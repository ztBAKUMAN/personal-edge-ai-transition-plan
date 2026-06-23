#include <iostream>
#include <memory>
#include <vector>

class TensorBuffer {
public:
    explicit TensorBuffer(size_t size) : size_(size), data_(std::make_unique<float[]>(size)) {
        std::cout << "TensorBuffer allocated " << size << " floats\n";
    }
    TensorBuffer(TensorBuffer&&) = default;
    TensorBuffer& operator=(TensorBuffer&&) = default;
    TensorBuffer(const TensorBuffer&) = delete;
    TensorBuffer& operator=(const TensorBuffer&) = delete;
    size_t size() const { return size_; }
    float* data() const { return data_.get(); }
private:
    size_t size_;
    std::unique_ptr<float[]> data_;
};

int main() {
    auto buf = std::make_unique<TensorBuffer>(1024);
    auto shared = std::make_shared<TensorBuffer>(512);
    auto weak = std::weak_ptr<TensorBuffer>(shared);
    if (auto locked = weak.lock()) {
        std::cout << "Shared buffer alive, size=" << locked->size() << "\n";
    }
    return 0;
}
