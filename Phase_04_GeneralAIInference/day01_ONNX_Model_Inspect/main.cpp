#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>

int main() {
    const char* model_path = "model.onnx";
    std::cout << "ONNX Model Inspector\n\n";

    // Minimal ONNX header reading
    std::ifstream file(model_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Model not found: " << model_path << "\n";
        std::cout << "\nExpected structure:\n";
        std::cout << "  Magic: \"ONNX\" (8 bytes)\n";
        std::cout << "  Header: ir_version, opset, producer\n";
        std::cout << "  Graph: inputs, outputs, initializers, nodes\n";
        return 0;
    }

    char magic[8];
    file.read(magic, 8);
    std::cout << "Magic: " << std::string(magic, 4) << "\n";
    file.close();

    std::cout << "\nRun this when model.onnx exists:\n";
    std::cout << "  python -c \"import onnx; m=onnx.load('model.onnx'); print(m)\"\n";
    std::cout << "  python -c \"import onnx; m=onnx.load('model.onnx'); "
              << "[print(i.name, i.type) for i in m.graph.input]\"\n";
    return 0;
}
