#include <iostream>

int main() {
    std::cout << "Docker for Edge AI Deployment\n\n";
    std::cout << "Why Docker for edge?\n";
    std::cout << "  1. Reproducible environment (CUDA/TensorRT/OpenCV versions)\n";
    std::cout << "  2. Isolated dependency management\n";
    std::cout << "  3. Cross-platform deployment (x86 -> ARM)\n\n";

    std::cout << "Dockerfile example:\n";
    std::cout << "  FROM nvcr.io/nvidia/tensorrt:22.12-py3\n";
    std::cout << "  RUN apt-get update && apt-get install -y libopencv-dev\n";
    std::cout << "  COPY ./build/edge-ai-service /app/\n";
    std::cout << "  CMD [\"/app/edge-ai-service\"]\n\n";

    std::cout << "Multi-arch build:\n";
    std::cout << "  docker buildx build --platform linux/arm64 -t edge-ai .\n";
    return 0;
}
