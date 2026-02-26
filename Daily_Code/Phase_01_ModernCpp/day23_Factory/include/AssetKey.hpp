#pragma once
#include <functional> // std::hash
#include <iostream>

// 自定义key
struct AssetKey {
    int type; // 资源类型 (比如: 1=Texture, 2=Sound, 3=Script)
    int id;   // 唯一ID

    // 重载operator==, 解决哈希冲突
    bool operator==(const AssetKey& other) const {
        return type == other.type && id == other.id;
    }

    // 重载<<, 方便日志打印
    friend std::ostream& operator<<(std::ostream& os, const AssetKey& k) {
        return os << "{Type:" << k.type << ", ID:" << k.id << "}";
    }
};

// 特化 std::hash 模板
namespace std {
    template <>
    struct hash<AssetKey> {
        // 重载 () 运算符, 仿函数
        size_t operator()(const AssetKey& k) const {
            size_t h1 = std::hash<int>()(k.type);
            size_t h2 = std::hash<int>()(k.id);

            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}