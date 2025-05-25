//
// Purpur Tentakel
// 17.05.25
//

#include <ranges>
#include <unordered_set>
#include <uil/global/asset.hpp>
#include <cpt/log.hpp>
#include <cpt/files.hpp>

namespace uil {
    AssetManager::AssetManager() : m_fallback_texture{ Texture2D{} } {
        auto const image   = GenImageColor(1, 1,MAGENTA);
        m_fallback_texture = LoadTextureFromImage(image);
        UnloadImage(image);
        cpt::log::info("[[Asset Manager]] | loaded fallback texture");
    }

    AssetManager::~AssetManager() {
        for (const auto& asset : m_assets | std::views::values) {
            UnloadTexture(asset);
        }
        UnloadTexture(m_fallback_texture);
        cpt::log::info("[[Asset Manager]] | unloaded all assets");
    }

    Texture2D const& AssetManager::get(cpt::usize const id) const {
        if (m_assets.contains(id)) {
            return m_assets.at(id);
        }

        static std::unordered_set<cpt::usize> already_warned{};
        if (already_warned.insert(id).second) { // is set to true if the insertion took place | This prevents spamming the console.
            cpt::log::error("[[Asset Manager]] | id '{}' missing | returning fallback texture", id);
        }
        
        return m_fallback_texture;
    }

    Texture2D const* AssetManager::get_ptr(cpt::usize const id) const {
        return &get(id);
    }

    tl::expected<cpt::usize, AssetManager::Error> AssetManager::load(std::filesystem::path const& path) {
        auto const texture = LoadTexture(cpt::make_absolute_path(path).string().c_str());
        if (not IsTextureValid(texture)) {
            cpt::log::error("[[Asset Manager]] | failed to load texture from the path '{}'", path.string());
            return tl::unexpected(Error::InvalidPath);
        }

        auto const id = m_next_id;
        ++m_next_id;
        m_assets[id] = texture;

        cpt::log::info("[[Asset Manager]] | loaded texture with id '{}' from the path '{}'", id, path.string());

        return id;
    }

    tl::expected<void, AssetManager::Error> AssetManager::unload(cpt::usize const id) {
        if (not m_assets.contains(id)) {
            cpt::log::error("[[Asset Manager]] | failed to unload id '{}'", id);
            return tl::unexpected(Error::InvalidId);
        }

        UnloadTexture(m_assets.at(id));
        m_assets.erase(id);

        cpt::log::info("[[Asset Manager]] | unloaded id '{}'", id);

        return {};
    }
}
