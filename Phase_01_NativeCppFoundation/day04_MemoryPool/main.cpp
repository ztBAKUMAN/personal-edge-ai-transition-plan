#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <cstddef>

struct alignas(64) Slot {
    char data[64];
};

class ObjectPool {
public:
    ObjectPool(size_t count) : storage_(count), free_list_(count) {
        for (size_t i = 0; i < count; ++i) {
            free_list_[i] = &storage_[i];
        }
    }

    Slot* acquire() {
        if (free_idx_ >= free_list_.size()) return nullptr;
        return free_list_[free_idx_++];
    }

    void release(Slot*) {
        // Simple bump allocator for demo
    }

private:
    std::vector<Slot> storage_;
    std::vector<Slot*> free_list_;
    size_t free_idx_ = 0;
};

int main() {
    ObjectPool pool(1000);
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        auto* s = pool.acquire();
        if (s) pool.release(s);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Pool operations: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " us\n";
    return 0;
}
