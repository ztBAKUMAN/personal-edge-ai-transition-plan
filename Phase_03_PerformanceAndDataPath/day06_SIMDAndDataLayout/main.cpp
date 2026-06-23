#include <iostream>
#include <cstdint>
#include <cstring>
#include <chrono>
#include <vector>

void scalar_add(const float* a, const float* b, float* c, size_t n) {
    for (size_t i = 0; i < n; ++i)
        c[i] = a[i] + b[i];
}

int main() {
    std::cout << "SIMD & data layout awareness\n\n";
    std::cout << "Manual vectorization requires:\n";
    std::cout << "  #include <xmmintrin.h>   // SSE\n";
    std::cout << "  #include <immintrin.h>    // AVX/AVX2\n";
    std::cout << "  #include <arm_neon.h>     // ARM NEON\n\n";

    std::cout << "Compile with optimization flags:\n";
    std::cout << "  g++ -O3 -march=native -ffast-math main.cpp\n";
    std::cout << "  -mavx2 -mfma (for AVX2+FMA)\n";
    std::cout << "  -march=armv8-a+simd (for ARM NEON)\n\n";

    constexpr size_t N = 1000000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);

    auto start = std::chrono::steady_clock::now();
    scalar_add(a.data(), b.data(), c.data(), N);
    auto end = std::chrono::steady_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Scalar add (" << N << " elements): " << us << " us\n";
    std::cout << "Last: " << c.back() << "\n";

    std::cout << "\nData layout: AoS vs SoA\n";
    std::cout << "  AoS: struct {float x,y,z;} points[N]  -- poor for SIMD\n";
    std::cout << "  SoA: float x[N], y[N], z[N]          -- SIMD friendly\n";
    return 0;
}
