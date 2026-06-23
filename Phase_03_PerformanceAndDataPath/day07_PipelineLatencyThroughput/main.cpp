#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

struct PipelineMetrics {
    double preprocess_ms;
    double inference_ms;
    double postprocess_ms;
    double total_ms;
    double fps;
};

void simulate_preprocess() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); }
void simulate_inference()  { std::this_thread::sleep_for(std::chrono::milliseconds(200)); }
void simulate_postprocess(){ std::this_thread::sleep_for(std::chrono::milliseconds(20)); }

int main() {
    std::cout << "Pipeline latency / throughput analysis\n\n";

    std::vector<PipelineMetrics> runs;
    for (int i = 0; i < 5; ++i) {
        auto start = std::chrono::steady_clock::now();

        auto t1 = std::chrono::steady_clock::now();
        simulate_preprocess();
        auto t2 = std::chrono::steady_clock::now();

        simulate_inference();
        auto t3 = std::chrono::steady_clock::now();

        simulate_postprocess();
        auto t4 = std::chrono::steady_clock::now();

        PipelineMetrics m;
        m.preprocess_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        m.inference_ms  = std::chrono::duration<double, std::milli>(t3 - t2).count();
        m.postprocess_ms= std::chrono::duration<double, std::milli>(t4 - t3).count();
        m.total_ms = std::chrono::duration<double, std::milli>(t4 - t1).count();
        m.fps = 1000.0 / m.total_ms;
        runs.push_back(m);
    }

    std::cout << "Run | Pre(ms) | Infer(ms) | Post(ms) | Total(ms) | FPS\n";
    std::cout << "----|---------|-----------|----------|-----------|-----\n";
    for (size_t i = 0; i < runs.size(); ++i) {
        auto& m = runs[i];
        std::cout << "  " << i << " | "
                  << m.preprocess_ms << "    | "
                  << m.inference_ms << "      | "
                  << m.postprocess_ms << "      | "
                  << m.total_ms << "       | "
                  << m.fps << "\n";
    }
    return 0;
}
