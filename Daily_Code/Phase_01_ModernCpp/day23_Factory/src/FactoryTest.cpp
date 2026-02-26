#include "AssetManager.hpp"

const int TYPE_TEXTURE = 1;
const int TYPE_SOUND   = 2;
const int TYPE_UNKNOWN = 99;

int main() {
    MyLogger::getInstance().open("factory_test.log");
    LOG_INFO("=== Asset Factory Test Start ===");

    AssetManager::getInstance().registerCreator(TYPE_TEXTURE, [](const AssetKey& k) {
        return std::make_shared<TextureAsset>(k);
    });
    
    AssetManager::getInstance().registerCreator(TYPE_SOUND, [](const AssetKey& k) {
        return std::make_shared<SoundAsset>(k);
    });

    AssetKey texKey = {TYPE_TEXTURE, 1001};
    AssetKey sndKey = {TYPE_SOUND,   2005};
    AssetKey badKey = {TYPE_UNKNOWN, 9999};

    auto tex = AssetManager::getInstance().getAsset(texKey); 
    auto snd = AssetManager::getInstance().getAsset(sndKey); 
    auto bad = AssetManager::getInstance().getAsset(badKey); 

    if (tex) tex->use(); // 调用的是 TextureAsset::use()
    if (snd) snd->use(); // 调用的是 SoundAsset::use()

    LOG_INFO("=== Test End ===");
    return 0;
}