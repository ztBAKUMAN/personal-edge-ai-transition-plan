#include <iostream>
#include <cstdint>
#include <cstring>

struct PacketHeader {
    uint32_t magic;
    uint32_t seq;
    uint16_t type;
    uint16_t length;
};

struct InferenceRequest {
    PacketHeader header;
    uint8_t model_id;
    uint32_t input_size;
    float threshold;
};

int main() {
    std::cout << "Protocol design demo\n";
    std::cout << "sizeof(PacketHeader) = " << sizeof(PacketHeader) << "\n";
    std::cout << "sizeof(InferenceRequest) = " << sizeof(InferenceRequest) << "\n\n";

    std::cout << "Key design considerations:\n";
    std::cout << "  1. Wire format: little-endian vs big-endian\n";
    std::cout << "  2. Alignment: no implicit padding in protocol\n";
    std::cout << "  3. Versioning: backward-compatible field extension\n";
    std::cout << "  4. Magic number: frame synchronization\n\n";

    InferenceRequest req{};
    req.header.magic = 0xED0101;
    req.header.type = 1;
    req.model_id = 0;
    req.input_size = 640 * 640 * 3;
    req.threshold = 0.5f;

    uint8_t buffer[sizeof(InferenceRequest)];
    memcpy(buffer, &req, sizeof(req));
    std::cout << "Serialized " << sizeof(buffer) << " bytes\n";
    return 0;
}
