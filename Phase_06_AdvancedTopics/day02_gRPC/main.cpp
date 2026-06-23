#include <iostream>

int main() {
    std::cout << "gRPC for Edge AI Service Communication\n\n";
    std::cout << "Why gRPC for edge:\n";
    std::cout << "  1. Strongly typed IDL (protobuf)\n";
    std::cout << "  2. HTTP/2 multiplexing (low latency)\n";
    std::cout << "  3. Streaming (video frame streaming)\n";
    std::cout << "  4. Bi-directional communication\n\n";

    std::cout << "Service definition (inference.proto):\n";
    std::cout << "  service InferenceService {\n";
    std::cout << "    rpc Detect(Image) returns (DetectionResults);\n";
    std::cout << "    rpc StreamFrames(stream Frame) returns (stream Result);\n";
    std::cout << "  }\n\n";

    std::cout << "Dependencies:\n";
    std::cout << "  grpc-cpp, protobuf, protoc\n";
    std::cout << "  apt install libgrpc++-dev protobuf-compiler-grpc\n";
    return 0;
}
