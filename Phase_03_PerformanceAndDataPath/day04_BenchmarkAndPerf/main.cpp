#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>

void bench_v1(const std::vector<float>& data, std::vector<float>& out) {
    for (size_t i = 0; i < data.size(); ++i)
        out[i] = data[i] * data[i] + data[i] * 2.0f + 1.0f;
}

void bench_v2(const std::vector<float>& data, std::vector<float>& out) {
    float* d = const_cast<float*>(data.data());
    for (size_t i = 0; i < data.size(); ++i)
        out[i] = (d[i] + 1.0f) * (d[i] + 1.0f);
}

int main() {
    constexpr size_t N = 10000000;
    std::vector<float> data(N), out(N);
    std::iota(data.begin(), data.end(), 0.0f);

    auto run = [&](auto&& func, const char* name) {
        auto start = std::chrono::steady_clock::now();
        for (int r = 0; r < 5; ++r) func(data, out);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << name << ": " << ms << " ms (5 runs)\n";
    };

    run(bench_v1, "V1 (direct)");
    run(bench_v2, "V2 (optimized)");
    std::cout << "\nFor deeper analysis: perf stat ./benchmark\n";
    return 0;
}
