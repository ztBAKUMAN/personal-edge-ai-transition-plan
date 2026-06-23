#include <iostream>
#include <string>
#include <vector>

class ImageBuffer {
public:
    ImageBuffer() : data_(nullptr), size_(0) {}
    ImageBuffer(size_t size) : data_(new uint8_t[size]), size_(size) {}
    ~ImageBuffer() { delete[] data_; }
    ImageBuffer(const ImageBuffer& other) : data_(new uint8_t[other.size_]), size_(other.size_) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy constructed\n";
    }
    ImageBuffer(ImageBuffer&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "Move constructed\n";
    }
    ImageBuffer& operator=(ImageBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
private:
    uint8_t* data_;
    size_t size_;
};

ImageBuffer createBuffer(size_t size) { return ImageBuffer(size); }

int main() {
    ImageBuffer buf1(1000);
    ImageBuffer buf2(std::move(buf1));
    ImageBuffer buf3 = createBuffer(500);
    std::cout << "Move semantics demo done\n";
    return 0;
}
