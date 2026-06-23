#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
#include <cassert>

template<typename T, size_t N>
class SPSCRingBuffer {
public:
    bool push(const T& value) {
        size_t current = write_idx_.load(std::memory_order_relaxed);
        size_t next = (current + 1) % N;
        if (next == read_idx_.load(std::memory_order_acquire))
            return false; // full
        buffer_[current] = value;
        write_idx_.store(next, std::memory_order_release);
        return true;
    }

    bool pop(T& value) {
        size_t current = read_idx_.load(std::memory_order_relaxed);
        if (current == write_idx_.load(std::memory_order_acquire))
            return false; // empty
        value = buffer_[current];
        read_idx_.store((current + 1) % N, std::memory_order_release);
        return true;
    }

private:
    T buffer_[N];
    std::atomic<size_t> read_idx_{0};
    std::atomic<size_t> write_idx_{0};
};

int main() {
    SPSCRingBuffer<int, 256> queue;
    std::vector<int> results;

    std::thread producer([&] {
        for (int i = 0; i < 1000; ++i) {
            while (!queue.push(i)) {}
        }
    });

    std::thread consumer([&] {
        int val;
        for (int i = 0; i < 1000; ++i) {
            while (!queue.pop(val)) {}
            results.push_back(val);
        }
    });

    producer.join(); consumer.join();
    std::cout << "SPSC queue: " << results.size() << " items transferred\n";
    return 0;
}
