#include <iostream>
#include <vector>
#include <thread>

// This file is designed to be compiled with sanitizers for testing.
// Build with: -fsanitize=address -g -O1 for ASan
// Build with: -fsanitize=undefined -g -O1 for UBSan
// Build with: -fsanitize=thread -g -O1 for TSan

void demo_stack_buffer_overflow() {
    int arr[5];
    for (int i = 0; i <= 5; ++i) {  // Off-by-one
        arr[i] = i;
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    }
}

void demo_data_race() {
    int counter = 0;
    std::thread t1([&]() { for (int i = 0; i < 100000; ++i) ++counter; });
    std::thread t2([&]() { for (int i = 0; i < 100000; ++i) ++counter; });
    t1.join(); t2.join();
    std::cout << "Counter (should be 200000): " << counter << "\n";
}

int main() {
    std::cout << "Run this with:\n";
    std::cout << "  ASan: -fsanitize=address -g -O1\n";
    std::cout << "  TSan: -fsanitize=thread -g -O1\n";
    std::cout << "  UBSan: -fsanitize=undefined -g -O1\n";
    demo_data_race();
    return 0;
}
