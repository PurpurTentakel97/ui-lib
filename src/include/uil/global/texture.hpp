//
// Purpur Tentakel
// 17.05.25
//

#pragma once

#include <filesystem>
#include <raylib.h>
#include <unordered_map>
#include <cpt/types.hpp>
#include <tl/expected.hpp>

namespace uil {
    class TextureManager final {
    public:
        enum class Error {
            InvalidPath,
            InvalidId,
        };

    private:
        cpt::usize m_next_id = 1;
        std::unordered_map<cpt::usize, Texture2D> m_assets{};
        Texture2D m_fallback_texture;

    public:
        TextureManager();
        TextureManager(const TextureManager&)            = delete;
        TextureManager(TextureManager&&)                 = delete;
        TextureManager& operator=(TextureManager const&) = delete;
        TextureManager& operator=(TextureManager&&)      = delete;
        ~TextureManager();

        [[nodiscard]] Texture2D const& get(cpt::usize id) const;
        [[nodiscard]] Texture2D const* get_ptr(cpt::usize id) const;

        [[nodiscard]] tl::expected<cpt::usize, Error> load(std::filesystem::path const& path);
        [[nodiscard]] tl::expected<void, Error> unload(cpt::usize id);
    };
}
