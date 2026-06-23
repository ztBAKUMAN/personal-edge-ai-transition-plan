#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Detection {
    int class_id;
    float confidence;
    float x, y, w, h;
};

float iou(const Detection& a, const Detection& b) {
    float x1 = std::max(a.x, b.x);
    float y1 = std::max(a.y, b.y);
    float x2 = std::min(a.x + a.w, b.x + b.w);
    float y2 = std::min(a.y + a.h, b.y + b.h);
    float inter = std::max(0.0f, x2 - x1) * std::max(0.0f, y2 - y1);
    float union_area = a.w * a.h + b.w * b.h - inter;
    return inter / union_area;
}

std::vector<Detection> nms(const std::vector<Detection>& detections, float threshold) {
    std::vector<Detection> result;
    auto sorted = detections;
    std::sort(sorted.begin(), sorted.end(),
              [](const Detection& a, const Detection& b) {
                  return a.confidence > b.confidence;
              });

    std::vector<bool> suppressed(sorted.size(), false);
    for (size_t i = 0; i < sorted.size(); ++i) {
        if (suppressed[i]) continue;
        result.push_back(sorted[i]);
        for (size_t j = i + 1; j < sorted.size(); ++j) {
            if (!suppressed[j] && iou(sorted[i], sorted[j]) > threshold)
                suppressed[j] = true;
        }
    }
    return result;
}

int main() {
    std::vector<Detection> dets = {
        {0, 0.9f, 10, 10, 50, 50},
        {0, 0.8f, 12, 12, 48, 48},  // overlaps with first
        {1, 0.7f, 100, 100, 30, 30},
        {0, 0.6f, 15, 15, 45, 45},  // overlaps with first
        {1, 0.5f, 200, 200, 40, 40},
    };

    auto filtered = nms(dets, 0.5f);
    std::cout << "Before NMS: " << dets.size() << " detections\n";
    std::cout << "After NMS:  " << filtered.size() << " detections\n";
    for (auto& d : filtered) {
        std::cout << "  Class=" << d.class_id
                  << " Conf=" << d.confidence
                  << " (" << d.x << "," << d.y << " "
                  << d.w << "x" << d.h << ")\n";
    }
    return 0;
}
