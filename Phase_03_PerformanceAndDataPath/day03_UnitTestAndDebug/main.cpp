#include <iostream>
#include <cassert>
#include <cmath>

// Simple unit test framework
#define TEST(name) std::cout << "TEST: " << name << "\n"
#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { std::cerr << "FAILED: " #cond << "\n"; return 1; } \
} while(0)
#define ASSERT_EQ(a, b) do { \
    if ((a) != (b)) { std::cerr << "FAILED: " #a "==" #b << "\n"; return 1; } \
} while(0)

float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(-x));
}

int argmax(const float* arr, size_t n) {
    int idx = 0;
    for (size_t i = 1; i < n; ++i)
        if (arr[i] > arr[idx]) idx = i;
    return idx;
}

int main() {
    TEST("sigmoid(0) == 0.5");
    ASSERT_TRUE(std::abs(sigmoid(0) - 0.5f) < 1e-6f);

    TEST("sigmoid is monotonic");
    ASSERT_TRUE(sigmoid(-10) < sigmoid(0));
    ASSERT_TRUE(sigmoid(0) < sigmoid(10));

    TEST("argmax returns index of max value");
    float data[] = {0.1f, 0.8f, 0.3f, 0.5f};
    ASSERT_EQ(argmax(data, 4), 1);

    std::cout << "All tests passed!\n";
    return 0;
}
