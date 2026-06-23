#include <iostream>
#include <cmath>

struct QuantizationMetrics {
    float fp32_accuracy;
    float int8_accuracy;
    float accuracy_loss;
    float speedup;
    float memory_reduction;
};

int main() {
    std::cout << "INT8 Quantization & Accuracy-Performance Tradeoff\n\n";

    QuantizationMetrics metrics{
        .fp32_accuracy = 0.856f,
        .int8_accuracy = 0.842f,
        .accuracy_loss = 1.4f,
        .speedup = 2.3f,
        .memory_reduction = 4.0f
    };

    std::cout << "Quantization Comparison:\n";
    std::cout << "  FP32 mAP:          " << metrics.fp32_accuracy << "\n";
    std::cout << "  INT8 mAP:          " << metrics.int8_accuracy << "\n";
    std::cout << "  Accuracy loss:     " << metrics.accuracy_loss << "%\n";
    std::cout << "  Speedup:           " << metrics.speedup << "x\n";
    std::cout << "  Memory reduction:  " << metrics.memory_reduction << "x\n\n";

    std::cout << "Calibration methods:\n";
    std::cout << "  1. Entropy calibration (default, best for vision)\n";
    std::cout << "  2. Percentile calibration\n";
    std::cout << "  3. Min-max calibration\n\n";

    std::cout << "Run with TensorRT:\n";
    std::cout << "  trtexec --onnx=model.onnx --saveEngine=model_fp32.trt\n";
    std::cout << "  trtexec --onnx=model.onnx --saveEngine=model_int8.trt "
              << "--int8 --calib=calibration_data\n";
    return 0;
}
