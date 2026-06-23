#include <iostream>
#include <cstddef>

struct alignas(64) CacheLineAligned {
    int value;
};

#pragma pack(push, 1)
struct PackedData {
    char a;
    int b;
    short c;
};
#pragma pack(pop)

struct AlignedData {
    char a;
    char pad[3];
    int b;
    short c;
};

int main() {
    std::cout << "Memory alignment demo:\n";
    std::cout << "  alignof(int) = " << alignof(int) << "\n";
    std::cout << "  alignof(double) = " << alignof(double) << "\n\n";

    std::cout << "  PackedData:  sizeof=" << sizeof(PackedData)
              << " (_packed)\n";
    std::cout << "  AlignedData: sizeof=" << sizeof(AlignedData)
              << " (with padding)\n";
    std::cout << "  CacheLineAligned: sizeof=" << sizeof(CacheLineAligned)
              << " align=" << alignof(CacheLineAligned) << "\n";

    std::cout << "\nWhy alignment matters for AI:\n";
    std::cout << "  - SIMD (AVX/NEON): requires 16/32-byte alignment\n";
    std::cout << "  - TensorRT: I/O buffers need 256-byte alignment\n";
    std::cout << "  - ARM CPUs: unaligned access causes exception\n";
    return 0;
}
