#include <iostream>

int main() {
    std::cout << "CUDA Programming for Edge AI\n\n";
    std::cout << "When CUDA on edge?\n";
    std::cout << "  - NVIDIA Jetson (Orin, Xavier, TX2)\n";
    std::cout << "  - GPU-accelerated preprocessing\n";
    std::cout << "  - Custom CUDA kernels for post-processing\n\n";

    std::cout << "Key API:\n";
    std::cout << "  #include <cuda_runtime.h>\n";
    std::cout << "  cudaMalloc(&dev, size);\n";
    std::cout << "  cudaMemcpy(dev, host, dir);\n";
    std::cout << "  kernel<<<grid, block>>>(dev);\n";
    std::cout << "  cudaFree(dev);\n\n";

    std::cout << "Example kernel (NMS on GPU):\n";
    std::cout << "  __global__ void nms_kernel(\n";
    std::cout << "    float* boxes, float* scores,\n";
    std::cout << "    int* keep, int num_boxes\n";
    std::cout << "  ) {\n";
    std::cout << "    int idx = blockIdx.x * blockDim.x + threadIdx.x;\n";
    std::cout << "    if (idx >= num_boxes) return;\n";
    std::cout << "    // parallel NMS computation\n";
    std::cout << "  }\n\n";

    std::cout << "Compile:\n";
    std::cout << "  nvcc -o cuda_demo main.cu -lcudart\n";
    return 0;
}
