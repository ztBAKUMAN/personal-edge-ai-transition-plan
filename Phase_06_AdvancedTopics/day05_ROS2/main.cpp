#include <iostream>

int main() {
    std::cout << "ROS2 for Robotic Edge AI\n\n";
    std::cout << "When to use ROS2:\n";
    std::cout << "  - Multi-sensor fusion (camera + LiDAR + IMU)\n";
    std::cout << "  - Distributed edge nodes (robot fleet)\n";
    std::cout << "  - Real-time control + AI inference\n\n";

    std::cout << "Key concepts:\n";
    std::cout << "  Node       - computation unit\n";
    std::cout << "  Topic      - pub/sub communication\n";
    std::cout << "  Service    - request/response\n";
    std::cout << "  Action     - long-running task with feedback\n\n";

    std::cout << "AI integration pattern:\n";
    std::cout << "  Camera node → Image topic →\n";
    std::cout << "  Detection node (ONNX/TensorRT) →\n";
    std::cout << "  BoundingBox topic → Control node\n";
    return 0;
}
