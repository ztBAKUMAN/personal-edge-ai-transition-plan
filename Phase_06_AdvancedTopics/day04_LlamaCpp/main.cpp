#include <iostream>

int main() {
    std::cout << "llama.cpp — LLM Inference on Edge\n\n";
    std::cout << "What is llama.cpp?\n";
    std::cout << "  - C++ implementation of LLaMA inference\n";
    std::cout << "  - No GPU required (optimized for CPU)\n";
    std::cout << "  - ARM NEON, x86 AVX2, CUDA support\n";
    std::cout << "  - 4-bit and 8-bit quantization\n\n";

    std::cout << "Edge AI use cases:\n";
    std::cout << "  1. Local LLM inference on edge devices\n";
    std::cout << "  2. Text summarization for sensor data\n";
    std::cout << "  3. On-device decision making (no cloud)\n\n";

    std::cout << "Integration:\n";
    std::cout << "  git clone https://github.com/ggerganov/llama.cpp\n";
    std::cout << "  cd llama.cpp && make\n";
    std::cout << "  ./main -m models/llama-2-7b.gguf -p \"Hello\"\n";
    return 0;
}
