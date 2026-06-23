#include <iostream>
#include <vector>
#include <string>

// ONNX Runtime C++ API stub
// In production: #include <onnxruntime_cxx_api.h>

int main() {
    std::cout << "ONNX Runtime C++ Inference\n\n";
    std::cout << "Dependencies:\n";
    std::cout << "  sudo apt install libonnxruntime-dev\n";
    std::cout << "  or: vcpkg install onnxruntime\n\n";

    std::cout << "Typical usage:\n";
    std::cout << "  OrtEnv* env = OrtEnv::Get();\n";
    std::cout << "  OrtSession* session = new OrtSession(env, model_path);\n";
    std::cout << "  OrtAllocator* allocator = Ort::GetAllocator();\n";
    std::cout << "  session->Run(...);\n\n";

    std::cout << "When model.onnx and libonnxruntime are available,\n";
    std::cout << "enable the ONNXRuntime include and link in CMakeLists.txt\n";
    return 0;
}
