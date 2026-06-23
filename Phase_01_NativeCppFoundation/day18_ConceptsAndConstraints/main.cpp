#include <iostream>
#include <concepts>
#include <type_traits>

template<typename T>
concept InferenceBackend = requires(T t) {
    { t.load(std::string{}) } -> std::same_as<bool>;
    { t.infer() } -> std::same_as<void>;
    { t.name() } -> std::convertible_to<std::string>;
};

struct ONNXBackend {
    bool load(const std::string& path) { std::cout << "Load " << path << "\n"; return true; }
    void infer() { std::cout << "ONNX infer\n"; }
    std::string name() const { return "ONNX"; }
};

template<InferenceBackend T>
void runInference(T& backend, const std::string& model) {
    backend.load(model);
    backend.infer();
}

int main() {
    static_assert(InferenceBackend<ONNXBackend>, "ONNXBackend must satisfy InferenceBackend concept");
    ONNXBackend backend;
    runInference(backend, "model.onnx");
    return 0;
}
