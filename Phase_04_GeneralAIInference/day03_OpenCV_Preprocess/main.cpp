#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

struct Image {
    int width, height, channels;
    std::vector<uint8_t> data;
};

struct PreprocessParams {
    int targetWidth = 640;
    int targetHeight = 640;
    float mean[3] = {0.485f, 0.456f, 0.406f};
    float std[3] = {0.229f, 0.224f, 0.225f};
};

std::vector<float> preprocess(const Image& img, const PreprocessParams& p) {
    std::vector<float> tensor(p.targetWidth * p.targetHeight * 3);

    for (int y = 0; y < p.targetHeight; ++y) {
        for (int x = 0; x < p.targetWidth; ++x) {
            int srcX = x * img.width / p.targetWidth;
            int srcY = y * img.height / p.targetHeight;
            int srcIdx = (srcY * img.width + srcX) * img.channels;

            for (int c = 0; c < 3; ++c) {
                float normalized = (img.data[srcIdx + c] / 255.0f - p.mean[c]) / p.std[c];
                tensor[c * p.targetHeight * p.targetWidth + y * p.targetWidth + x] = normalized;
            }
        }
    }
    return tensor;
}

int main() {
    Image img{1920, 1080, 3, std::vector<uint8_t>(1920 * 1080 * 3, 128)};
    PreprocessParams params;

    auto tensor = preprocess(img, params);
    std::cout << "Preprocessed tensor: " << tensor.size() << " floats ("
              << tensor.size() * 4 / 1024 << " KB)\n";
    std::cout << "Layout: CHW (channel-first)\n";
    std::cout << "First value: " << tensor[0] << "\n";
    return 0;
}
