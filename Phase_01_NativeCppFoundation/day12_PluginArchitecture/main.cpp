#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <dlfcn.h>

class IInferenceBackend {
public:
    virtual ~IInferenceBackend() = default;
    virtual std::string name() const = 0;
    virtual bool load(const std::string& modelPath) = 0;
    virtual void infer() = 0;
};

class ONNXBackend : public IInferenceBackend {
public:
    std::string name() const override { return "ONNX Runtime"; }
    bool load(const std::string& path) override {
        std::cout << "Loading ONNX model: " << path << "\n";
        return true;
    }
    void infer() override { std::cout << "ONNX inference\n"; }
};

class PluginRegistry {
public:
    using Factory = std::function<std::unique_ptr<IInferenceBackend>()>;

    static PluginRegistry& instance() {
        static PluginRegistry reg;
        return reg;
    }

    void registerFactory(const std::string& name, Factory factory) {
        factories_[name] = std::move(factory);
    }

    std::unique_ptr<IInferenceBackend> create(const std::string& name) {
        auto it = factories_.find(name);
        if (it != factories_.end()) return it->second();
        return nullptr;
    }

private:
    std::unordered_map<std::string, Factory> factories_;
};

int main() {
    PluginRegistry::instance().registerFactory("onnxruntime", [] {
        return std::make_unique<ONNXBackend>();
    });

    auto backend = PluginRegistry::instance().create("onnxruntime");
    if (backend) {
        backend->load("model.onnx");
        backend->infer();
    }
    return 0;
}
