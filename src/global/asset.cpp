//
// Purpur Tentakel
// 17.05.25
//

#include <ranges>
#include <uil/global/asset.hpp>

namespace uil {
AssetManager::~AssetManager() {
    for (const auto &asset : m_assets | std::views::values) {
        UnloadTexture(asset);
    }
}
}
