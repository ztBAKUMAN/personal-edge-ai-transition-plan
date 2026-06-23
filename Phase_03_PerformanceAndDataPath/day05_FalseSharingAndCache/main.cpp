#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

struct alignas(64) PaddedCounter {
    std::atomic<int> value{0};
    char padding[60]; // fill cache line
};

struct UnpaddedCounter {
    std::atomic<int> value{0};
};

int main() {
    constexpr int N = 4;
    constexpr int ITERS = 10000000;

    // False sharing test
    {
        std::vector<UnpaddedCounter> counters(N);
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < N; ++i) {
            threads.emplace_back([&counters, i] {
                for (int j = 0; j < ITERS; ++j)
                    counters[i].value.fetch_add(1, std::memory_order_relaxed);
            });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::steady_clock::now();
        std::cout << "False sharing (unpadded): "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

    {
        std::vector<PaddedCounter> counters(N);
        auto start = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        for (int i = 0; i < N; ++i) {
            threads.emplace_back([&counters, i] {
                for (int j = 0; j < ITERS; ++j)
                    counters[i].value.fetch_add(1, std::memory_order_relaxed);
            });
        }
        for (auto& t : threads) t.join();
        auto end = std::chrono::steady_clock::now();
        std::cout << "No false sharing (padded): "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }
    return 0;
}
