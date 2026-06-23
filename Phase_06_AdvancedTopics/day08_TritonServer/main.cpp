#include <iostream>

int main() {
    std::cout << "Triton Inference Server\n\n";
    std::cout << "NVIDIA Triton (formerly TensorRT Inference Server):\n";
    std::cout << "  - Multi-model serving (ONNX, TensorRT, PyTorch)\n";
    std::cout << "  - Dynamic batching\n";
    std::cout << "  - Model version management\n";
    std::cout << "  - gRPC/REST API\n\n";

    std::cout << "Model repository structure:\n";
    std::cout << "  model_repository/\n";
    std::cout << "    yolov8/\n";
    std::cout << "      1/\n";
    std::cout << "        model.onnx\n";
    std::cout << "        config.pbtxt\n\n";

    std::cout << "config.pbtxt:\n";
    std::cout << "  name: \"yolov8\"\n";
    std::cout << "  platform: \"onnxruntime_onnx\"\n";
    std::cout << "  max_batch_size: 32\n";
    std::cout << "  input [ { name: \"images\" ... } ]\n";
    std::cout << "  output [ { name: \"output0\" ... } ]\n\n";

    std::cout << "C++ client:\n";
    std::cout << "  #include \"tritonclient.h\"\n";
    std::cout << "  TritonClient client(\"localhost:8001\");\n";
    std::cout << "  client.infer(\"yolov8\", inputs, &outputs);\n";
    return 0;
}
