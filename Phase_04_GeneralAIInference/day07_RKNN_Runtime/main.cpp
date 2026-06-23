#include <iostream>

int main() {
    std::cout << "RKNN Runtime (Rockchip NPU)\n\n";
    std::cout << "Dependencies:\n";
    std::cout << "  rknn-toolkit2 (PC, model conversion)\n";
    std::cout << "  librknnrt.so (target device, runtime)\n\n";

    std::cout << "Conversion:\n";
    std::cout << "  python converter.py --onnx model.onnx --rknn model.rknn\n\n";

    std::cout << "C++ API:\n";
    std::cout << "  #include <rknn_api.h>\n";
    std::cout << "  rknn_context ctx;\n";
    std::cout << "  rknn_init(&ctx, model_data, model_size, 0, nullptr);\n";
    std::cout << "  rknn_run(ctx, &inputs);\n";
    std::cout << "  rknn_outputs_get(ctx, n_outputs, &outputs);\n\n";

    std::cout << "Target devices: RK3588, RK3568, RV1106\n";
    return 0;
}
