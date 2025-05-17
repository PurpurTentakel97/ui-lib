//
// Purpur Tentakel
// 17.05.25
//

#pragma once

#include <raylib.h>
#include <unordered_map>
#include <cpt/types.hpp>

namespace uil {
    class AssetManager final {
    private:
        std::unordered_map<cpt::usize, Texture2D> m_assets{};

    public:
        AssetManager() = default;
        AssetManager(const AssetManager&) = delete;
        AssetManager(AssetManager&&) = delete;
        AssetManager& operator=(AssetManager const&) = delete;
        AssetManager& operator=(AssetManager&&) = delete;
        ~AssetManager();
    };
}
