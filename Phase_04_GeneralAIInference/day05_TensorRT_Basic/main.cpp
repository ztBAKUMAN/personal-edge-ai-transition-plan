#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    std::cout << "TensorRT Basic Inference\n\n";
    std::cout << "Dependencies:\n";
    std::cout << "  TensorRT 8.x+ (NVIDIA GPU required)\n";
    std::cout << "  CUDA 11.x+\n";
    std::cout << "  libnvinfer.so, libcudart.so\n\n";

    std::cout << "Workflow:\n";
    std::cout << "  1. Build engine: onnx2trt or trtexec\n";
    std::cout << "     trtexec --onnx=model.onnx --saveEngine=model.trt\n\n";

    std::cout << "  2. C++ inference:\n";
    std::cout << "     IRuntime* runtime = createInferRuntime(logger);\n";
    std::cout << "     ICudaEngine* engine = runtime->deserializeCudaEngine(trt_model);\n";
    std::cout << "     IExecutionContext* ctx = engine->createExecutionContext();\n";
    std::cout << "     ctx->enqueueV3(stream);\n\n";

    std::cout << "Engine file: model.trt (typically 10-50 MB)\n";
    return 0;
}
