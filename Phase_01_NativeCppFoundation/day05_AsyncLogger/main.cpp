#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <atomic>

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

class AsyncLogger {
public:
    static AsyncLogger& instance() {
        static AsyncLogger logger;
        return logger;
    }

    void open(const std::string& filename) {
        std::lock_guard<std::mutex> lock(file_mutex_);
        if (file_.is_open()) file_.close();
        file_.open(filename, std::ios::out | std::ios::app);
    }

    template <typename... Args>
    void log(LogLevel level, const char* file, int line, Args... args) {
        std::ostringstream ss;
        auto now = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        ss << "[" << std::put_time(std::localtime(&now), "%H:%M:%S") << "]";

        switch (level) {
            case LogLevel::DEBUG: ss << "[DEBUG] "; break;
            case LogLevel::INFO:  ss << "[INFO]  "; break;
            case LogLevel::WARN:  ss << "[WARN]  "; break;
            case LogLevel::ERROR: ss << "[ERROR] "; break;
        }
        ((ss << args << " "), ...);
        ss << " (" << file << ":" << line << ")\n";

        std::cout << ss.str();
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            queue_.push(ss.str());
        }
        cv_.notify_one();
    }

private:
    AsyncLogger() : exit_(false) {
        open("app.log");
        worker_ = std::thread(&AsyncLogger::process, this);
    }

    ~AsyncLogger() {
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            exit_ = true;
        }
        cv_.notify_all();
        if (worker_.joinable()) worker_.join();
        if (file_.is_open()) {
            file_.flush();
            file_.close();
        }
    }

    AsyncLogger(const AsyncLogger&) = delete;
    AsyncLogger& operator=(const AsyncLogger&) = delete;

    void process() {
        while (true) {
            std::queue<std::string> batch;
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                cv_.wait(lock, [this] {
                    return !queue_.empty() || exit_;
                });
                if (exit_ && queue_.empty()) return;
                std::swap(batch, queue_);
            }
            while (!batch.empty()) {
                if (file_.is_open()) {
                    file_ << batch.front();
                    file_.flush();
                }
                batch.pop();
            }
        }
    }

    std::mutex file_mutex_;
    std::ofstream file_;
    std::mutex queue_mutex_;
    std::condition_variable cv_;
    std::queue<std::string> queue_;
    std::thread worker_;
    std::atomic<bool> exit_;
};

#define LOG_DEBUG(...) AsyncLogger::instance().log(LogLevel::DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  AsyncLogger::instance().log(LogLevel::INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  AsyncLogger::instance().log(LogLevel::WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) AsyncLogger::instance().log(LogLevel::ERROR, __FILE__, __LINE__, __VA_ARGS__)

int main() {
    LOG_INFO("AsyncLogger started");
    for (int i = 0; i < 5; ++i) {
        LOG_DEBUG("iteration", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    LOG_INFO("AsyncLogger done");
    return 0;
}
