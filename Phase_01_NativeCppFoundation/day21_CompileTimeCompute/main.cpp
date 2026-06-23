#include <iostream>
#include <array>

constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }
constexpr int squared(int n) { return n * n; }

consteval int compileTimeOnly(int n) { return n * n * n; }

template<int N>
struct ShapeValidator {
    static_assert(N > 0 && N % 32 == 0, "Input size must be multiple of 32");
    static constexpr int value = N;
};

int main() {
    constexpr auto fact5 = factorial(5);
    constexpr auto sq = squared(16);
    constexpr auto cube = compileTimeOnly(3);
    std::cout << "factorial(5)=" << fact5
              << " squared(16)=" << sq
              << " cubed(3)=" << cube << "\n";

    constexpr ShapeValidator<640> input;
    std::cout << "Validated input size: " << input.value << "\n";
    return 0;
}
