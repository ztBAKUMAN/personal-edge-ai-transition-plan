#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <sstream>
#include <mutex>

namespace fs = std::filesystem;

struct InferenceConfig {
    std::string modelPath = "models/default.onnx";
    std::string backend = "onnxruntime";
    float scoreThreshold = 0.5f;
    float nmsThreshold = 0.45f;
    int batchSize = 1;
    int inputWidth = 640;
    int inputHeight = 640;
    int deviceId = 0;
    bool useFP16 = false;
};

class ConfigManager {
public:
    static ConfigManager& instance() {
        static ConfigManager mgr;
        return mgr;
    }

    InferenceConfig get() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return config_;
    }

    void set(const InferenceConfig& cfg) {
        std::lock_guard<std::mutex> lock(mutex_);
        config_ = cfg;
    }

    bool load(const std::string& path) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!fs::exists(path)) {
            std::cerr << "Config not found: " << path << "\n";
            return false;
        }
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open: " << path << "\n";
            return false;
        }
        std::stringstream ss;
        ss << file.rdbuf();
        config_ = parse(ss.str());
        return true;
    }

    bool save(const std::string& path) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::ofstream file(path);
        if (!file.is_open()) return false;
        file << serialize(config_);
        return true;
    }

private:
    ConfigManager() {
        auto defaultPath = "config.ini";
        if (fs::exists(defaultPath)) load(defaultPath);
    }

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    static std::unordered_map<std::string, std::string> parseKV(const std::string& text) {
        std::unordered_map<std::string, std::string> kv;
        std::istringstream iss(text);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.empty() || line[0] == '#' || line[0] == ';') continue;
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;
            auto key = line.substr(0, pos);
            auto val = line.substr(pos + 1);
            key.erase(key.find_last_not_of(" \t") + 1);
            val.erase(0, val.find_first_not_of(" \t"));
            kv[key] = val;
        }
        return kv;
    }

    static InferenceConfig parse(const std::string& text) {
        InferenceConfig cfg;
        auto kv = parseKV(text);
        if (kv.count("modelPath")) cfg.modelPath = kv["modelPath"];
        if (kv.count("backend")) cfg.backend = kv["backend"];
        if (kv.count("scoreThreshold")) cfg.scoreThreshold = std::stof(kv["scoreThreshold"]);
        if (kv.count("nmsThreshold")) cfg.nmsThreshold = std::stof(kv["nmsThreshold"]);
        if (kv.count("batchSize")) cfg.batchSize = std::stoi(kv["batchSize"]);
        if (kv.count("inputWidth")) cfg.inputWidth = std::stoi(kv["inputWidth"]);
        if (kv.count("inputHeight")) cfg.inputHeight = std::stoi(kv["inputHeight"]);
        if (kv.count("deviceId")) cfg.deviceId = std::stoi(kv["deviceId"]);
        if (kv.count("useFP16")) cfg.useFP16 = (kv["useFP16"] == "true");
        return cfg;
    }

    static std::string serialize(const InferenceConfig& cfg) {
        std::ostringstream oss;
        oss << "# Edge AI Inference Config\n";
        oss << "modelPath=" << cfg.modelPath << "\n";
        oss << "backend=" << cfg.backend << "\n";
        oss << "scoreThreshold=" << cfg.scoreThreshold << "\n";
        oss << "nmsThreshold=" << cfg.nmsThreshold << "\n";
        oss << "batchSize=" << cfg.batchSize << "\n";
        oss << "inputWidth=" << cfg.inputWidth << "\n";
        oss << "inputHeight=" << cfg.inputHeight << "\n";
        oss << "deviceId=" << cfg.deviceId << "\n";
        oss << "useFP16=" << (cfg.useFP16 ? "true" : "false") << "\n";
        return oss.str();
    }

    mutable std::mutex mutex_;
    InferenceConfig config_;
};

int main() {
    InferenceConfig cfg;
    cfg.modelPath = "models/yolov8s.onnx";
    cfg.backend = "onnxruntime";
    cfg.scoreThreshold = 0.6f;

    ConfigManager::instance().set(cfg);
    ConfigManager::instance().save("test_config.ini");

    auto loaded = ConfigManager::instance().get();
    std::cout << "Model: " << loaded.modelPath << "\n";
    std::cout << "Backend: " << loaded.backend << "\n";
    std::cout << "Threshold: " << loaded.scoreThreshold << "\n";
    return 0;
}
