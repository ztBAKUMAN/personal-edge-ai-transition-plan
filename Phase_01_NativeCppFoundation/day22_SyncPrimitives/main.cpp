#include <iostream>
#include <thread>
#include <latch>
#include <barrier>
#include <semaphore>
#include <vector>
#include <syncstream>

int main() {
    // latch: one-time synchronization
    std::latch workDone(3);
    std::vector<std::jthread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back([&workDone, i] {
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * i));
            std::osyncstream(std::cout) << "Thread " << i << " done\n";
            workDone.count_down();
        });
    }
    workDone.wait();
    std::cout << "All threads completed\n";

    // binary semaphore
    std::binary_semaphore sem(1);
    sem.acquire();
    std::cout << "Semaphore acquired\n";
    sem.release();
    std::cout << "Semaphore released\n";
    return 0;
}
