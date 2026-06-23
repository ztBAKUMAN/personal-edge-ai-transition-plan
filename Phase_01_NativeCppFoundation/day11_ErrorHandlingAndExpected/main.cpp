#include <iostream>
#include <variant>
#include <string>

struct InferenceError {
    enum Type { ModelNotFound, BackendError, OutOfMemory };
    Type type;
    std::string message;
};

struct InferenceResult {
    int value;
};

using Outcome = std::variant<InferenceResult, InferenceError>;

Outcome runInference(const std::string& model) {
    if (model.empty()) return InferenceError{InferenceError::ModelNotFound, "Model path empty"};
    return InferenceResult{42};
}

int main() {
    auto result = runInference("model.onnx");
    if (std::holds_alternative<InferenceResult>(result)) {
        std::cout << "Inference result: " << std::get<InferenceResult>(result).value << "\n";
    } else {
        auto& err = std::get<InferenceError>(result);
        std::cout << "Error type=" << err.type << " msg=" << err.message << "\n";
    }
    return 0;
}
