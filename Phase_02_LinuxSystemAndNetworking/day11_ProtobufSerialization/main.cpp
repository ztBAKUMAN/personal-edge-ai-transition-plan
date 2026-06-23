#include <iostream>
#include <string>
#include <vector>
#include <cstring>

// Minimal protobuf-style serialization demo
// In production, include <google/protobuf/message.h>

struct InferenceResult {
    int class_id;
    float confidence;
    float x, y, w, h;

    std::string serialize() const {
        std::string out;
        auto append = [&](const auto& val) {
            out.append(reinterpret_cast<const char*>(&val), sizeof(val));
        };
        append(class_id);
        append(confidence);
        append(x); append(y); append(w); append(h);
        return out;
    }

    static InferenceResult deserialize(const std::string& data) {
        InferenceResult r;
        const char* p = data.data();
        auto read = [&](auto& val) {
            memcpy(&val, p, sizeof(val));
            p += sizeof(val);
        };
        read(r.class_id);
        read(r.confidence);
        read(r.x); read(r.y); read(r.w); read(r.h);
        return r;
    }
};

int main() {
    InferenceResult r{1, 0.85f, 100, 200, 50, 80};
    auto data = r.serialize();
    auto back = InferenceResult::deserialize(data);

    std::cout << "Serialized size: " << data.size() << " bytes\n";
    std::cout << "Round-trip: class=" << back.class_id
              << " conf=" << back.confidence << "\n";
    std::cout << "\nFor production, use google::protobuf or flatbuffers\n";
    return 0;
}
