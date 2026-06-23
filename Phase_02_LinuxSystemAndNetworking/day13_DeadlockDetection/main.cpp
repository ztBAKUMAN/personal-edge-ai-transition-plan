#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Deadlock simulation
std::mutex mtx_a, mtx_b;

void thread1() {
    std::lock_guard<std::mutex> lock1(mtx_a);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(mtx_b);
    std::cout << "Thread 1 acquired both locks\n";
}

void thread2() {
    std::lock_guard<std::mutex> lock1(mtx_b);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lock2(mtx_a);
    std::cout << "Thread 2 acquired both locks\n";
}

int main() {
    std::cout << "Deadlock detection demo\n";
    std::cout << "Run: g++ main.cpp -g -fsanitize=thread\n";
    std::cout << "\nPrevention strategies:\n";
    std::cout << "  1. Fixed lock ordering (always lock A then B)\n";
    std::cout << "  2. std::lock() with std::adopt_lock\n";
    std::cout << "  3. TryLock with timeout\n";
    std::cout << "  4. Lock-free data structures\n";
    std::cout << "\nDetection tools:\n";
    std::cout << "  gdb: thread apply all bt\n";
    std::cout << "  helgrind: valgrind --tool=helgrind\n";
    std::cout << "  TSan: -fsanitize=thread\n";

    // Uncomment to trigger deadlock:
    // std::thread t1(thread1), t2(thread2);
    // t1.join(); t2.join();
    return 0;
}
