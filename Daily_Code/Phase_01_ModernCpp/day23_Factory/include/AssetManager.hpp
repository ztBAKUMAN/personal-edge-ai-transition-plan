#pragma once
#include "MyLogger.hpp"
#include "AssetKey.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

class Asset
{
public:
    explicit Asset(const AssetKey& key) : m_key(key){}
    virtual ~Asset() = default;
    virtual void use() const = 0;
    AssetKey getKey() const {return m_key;}
protected:
    AssetKey m_key;
};

// 派生类 1：贴图资源
class TextureAsset : public Asset {
public:
    explicit TextureAsset(const AssetKey& key) : Asset(key) {
        LOG_INFO("[Texture] Loading graphic data for ", m_key);
    }
    void use() const override {
        LOG_INFO("Drawing Texture on screen: ", m_key);
    }
};

// 派生类 2：音效资源
class SoundAsset : public Asset {
public:
    explicit SoundAsset(const AssetKey& key) : Asset(key) {
        LOG_INFO("[Sound] Loading audio wave for ", m_key);
    }
    void use() const override {
        LOG_INFO("Playing Sound: ", m_key);
    }
};

class AssetManager
{
public:
    static AssetManager& getInstance()
    {
        static AssetManager ins;
        return ins;
    }

    // 注册创建者
    void registerCreator(int type, std::function<std::shared_ptr<Asset>(const AssetKey&)> creator) {
        m_creators[type] = creator;
        LOG_INFO("[Manager] Registered creator for asset type: ", type);
    }

    std::shared_ptr<Asset> getAsset(const AssetKey& key)
    {
        // 检查缓存是否命中
        auto it = m_cache.find(key);
        if(it != m_cache.end())
        {
            std::shared_ptr<Asset> sharedAsset = it->second.lock();
            if(sharedAsset)
            {
                LOG_INFO("[Manager] Returning existing asset: ", key);
                return sharedAsset;
            }
            else
            {
                LOG_DEBUG("[Manager] Cache expired!");
                m_cache.erase(it);
            }
        }

        // 缓存没命中，创建新资源
        auto creatorIt = m_creators.find(key.type);
        if (creatorIt == m_creators.end()) 
        {
            LOG_ERROR("[Manager] Unknown asset type! Cannot create: ", key);
            return nullptr;
        }

        LOG_INFO("[Manager] Loading new asset...");
        // 调用回调函数指针生成对象
        std::shared_ptr<Asset> newAsset = creatorIt->second(key);
        m_cache[key] = newAsset;
        return newAsset;
    }
private:
    AssetManager() = default;
    AssetManager(const AssetManager& obj) = delete;
    AssetManager& operator=(const AssetManager& obj) = delete;

    std::unordered_map<AssetKey, std::weak_ptr<Asset>> m_cache;

    std::unordered_map<int, std::function<std::shared_ptr<Asset>(const AssetKey&)>> m_creators;
};