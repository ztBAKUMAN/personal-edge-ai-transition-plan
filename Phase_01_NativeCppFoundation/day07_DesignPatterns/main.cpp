#include <iostream>
#include <memory>
#include <string>

// Strategy pattern
class IInferenceBackend {
public:
    virtual ~IInferenceBackend() = default;
    virtual std::string name() const = 0;
    virtual void infer() = 0;
};

class ONNXBackend : public IInferenceBackend {
public:
    std::string name() const override { return "ONNX Runtime"; }
    void infer() override { std::cout << "ONNX inference\n"; }
};

class TensorRTBackend : public IInferenceBackend {
public:
    std::string name() const override { return "TensorRT"; }
    void infer() override { std::cout << "TensorRT inference\n"; }
};

// Factory pattern
enum class BackendType { ONNX, TENSORRT };
std::unique_ptr<IInferenceBackend> createBackend(BackendType type) {
    switch (type) {
        case BackendType::ONNX:     return std::make_unique<ONNXBackend>();
        case BackendType::TENSORRT: return std::make_unique<TensorRTBackend>();
    }
    return nullptr;
}

int main() {
    auto backend = createBackend(BackendType::ONNX);
    std::cout << "Using: " << backend->name() << "\n";
    backend->infer();
    return 0;
}
