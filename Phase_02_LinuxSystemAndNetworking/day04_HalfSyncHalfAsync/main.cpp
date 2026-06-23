#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>

class HalfSyncHalfAsync {
public:
    HalfSyncHalfAsync() : worker_(&HalfSyncHalfAsync::process, this) {}

    void submit(std::function<void()> task) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(task));
        cv_.notify_one();
    }

    ~HalfSyncHalfAsync() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        cv_.notify_one();
        worker_.join();
    }

private:
    void process() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return !queue_.empty() || stop_; });
                if (stop_ && queue_.empty()) return;
                task = std::move(queue_.front());
                queue_.pop();
            }
            task();
        }
    }

    std::queue<std::function<void()>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::thread worker_;
    bool stop_ = false;
};

int main() {
    HalfSyncHalfAsync reactor;
    reactor.submit([] { std::cout << "Async task 1\n"; });
    reactor.submit([] { std::cout << "Async task 2\n"; });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
