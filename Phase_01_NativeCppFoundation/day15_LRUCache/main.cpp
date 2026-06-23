#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

template<typename K, typename V>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {}

    V get(const K& key) {
        auto it = map_.find(key);
        if (it == map_.end()) return V{};
        moveToFront(it->second);
        return it->second->second;
    }

    void put(const K& key, const V& value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->second = value;
            moveToFront(it->second);
            return;
        }
        if (list_.size() >= capacity_) {
            auto last = list_.back();
            map_.erase(last.first);
            list_.pop_back();
        }
        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }

    void print() {
        for (auto& p : list_) std::cout << "(" << p.first << ":" << p.second << ") ";
        std::cout << "\n";
    }

private:
    using List = std::list<std::pair<K, V>>;
    using Iter = typename List::iterator;

    void moveToFront(Iter it) {
        list_.splice(list_.begin(), list_, it);
    }

    size_t capacity_;
    List list_;
    std::unordered_map<K, Iter> map_;
};

int main() {
    LRUCache<int, std::string> cache(3);
    cache.put(1, "a"); cache.put(2, "b"); cache.put(3, "c");
    std::cout << "get(1): " << cache.get(1) << "\n";
    cache.put(4, "d");
    cache.print();
    return 0;
}
