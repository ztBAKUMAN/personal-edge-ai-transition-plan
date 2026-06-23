#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include <typeindex>

struct Event { virtual ~Event() = default; };
struct FrameEvent : Event {
    FrameEvent(int cam, uint64_t t) : cameraId(cam), ts(t) {}
    int cameraId; uint64_t ts;
};
struct ResultEvent : Event {
    ResultEvent(int d, float c) : detections(d), confidence(c) {}
    int detections; float confidence;
};

class EventBus {
public:
    using Handler = std::function<void(const Event&)>;

    template<typename T>
    void subscribe(Handler handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        handlers_[std::type_index(typeid(T))].push_back(std::move(handler));
    }

    void publish(const Event& event) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = handlers_.find(std::type_index(typeid(event)));
        if (it != handlers_.end()) {
            for (auto& h : it->second) h(event);
        }
    }

private:
    std::mutex mutex_;
    std::unordered_map<std::type_index, std::vector<Handler>> handlers_;
};

int main() {
    EventBus bus;
    bus.subscribe<FrameEvent>([](const Event& e) {
        auto& fe = static_cast<const FrameEvent&>(e);
        std::cout << "Frame from camera " << fe.cameraId << "\n";
    });
    bus.subscribe<ResultEvent>([](const Event& e) {
        auto& re = static_cast<const ResultEvent&>(e);
        std::cout << re.detections << " objects, conf=" << re.confidence << "\n";
    });

    FrameEvent fe{1, 1000};
    ResultEvent re{3, 0.85f};
    bus.publish(fe);
    bus.publish(re);
    return 0;
}
