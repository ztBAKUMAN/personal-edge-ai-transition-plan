#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <vector>

struct Frame {
    int id;
    std::vector<uint8_t> data;
};

struct Result {
    int frame_id;
    int detections;
    float latency_ms;
};

class PipelineStage {
public:
    using ProcessFn = std::function<void(Frame, std::function<void(Result)>)>;

    PipelineStage(const std::string& name, ProcessFn fn, int workers = 2)
        : name_(name), fn_(std::move(fn)) {
        for (int i = 0; i < workers; ++i) {
            threads_.emplace_back([this] { workerLoop(); });
        }
    }

    void submit(Frame frame, std::function<void(Result)> callback) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push({std::move(frame), std::move(callback)});
        }
        cv_.notify_one();
    }

    ~PipelineStage() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        cv_.notify_all();
        for (auto& t : threads_) t.join();
    }

private:
    struct Task {
        Frame frame;
        std::function<void(Result)> callback;
    };

    void workerLoop() {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return !queue_.empty() || stop_; });
                if (stop_ && queue_.empty()) return;
                task = std::move(queue_.front());
                queue_.pop();
            }
            fn_(std::move(task.frame), std::move(task.callback));
        }
    }

    std::string name_;
    ProcessFn fn_;
    std::queue<Task> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::vector<std::thread> threads_;
    bool stop_ = false;
};

int main() {
    std::cout << "Multi-Model Pipeline\n\n";

    PipelineStage preprocess("preprocess", [](Frame f, auto cb) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cb({f.id, 0, 50});
    }, 2);

    PipelineStage detect("detect", [](Frame f, auto cb) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        cb({f.id, 3, 200});
    }, 1);

    PipelineStage classify("classify", [](Frame f, auto cb) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cb({f.id, 5, 100});
    }, 1);

    auto callback = [](Result r) {
        std::cout << "Frame " << r.frame_id
                  << ": " << r.detections << " detections, "
                  << r.latency_ms << " ms\n";
    };

    for (int i = 0; i < 5; ++i) {
        Frame f{i, std::vector<uint8_t>(640*480*3)};
        preprocess.submit(std::move(f), callback);
        detect.submit(std::move(f), callback);
        classify.submit(std::move(f), callback);
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
