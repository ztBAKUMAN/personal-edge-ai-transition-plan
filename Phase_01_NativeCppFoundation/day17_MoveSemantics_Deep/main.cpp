#include <iostream>
#include <string>
#include <vector>

class Buffer {
public:
    Buffer() : data_(nullptr), size_(0) {}
    explicit Buffer(size_t size) : data_(new char[size]), size_(size) {}

    ~Buffer() { delete[] data_; }

    Buffer(const Buffer& other) : data_(new char[other.size_]), size_(other.size_) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "deep copy, size=" << size_ << "\n";
    }

    Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "move, transferring ownership\n";
    }

    Buffer& operator=(Buffer other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(Buffer& a, Buffer& b) noexcept {
        std::swap(a.data_, b.data_);
        std::swap(a.size_, b.size_);
    }

private:
    char* data_;
    size_t size_;
};

int main() {
    Buffer a(100), b(200);
    a = std::move(b);
    Buffer c = std::move(a);
    std::cout << "Move semantics with RAII done\n";
    return 0;
}
