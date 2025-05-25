//
// Purpur Tentakel
// 25.05.25
//

#pragma once

#include <filesystem>
#include <unordered_map>
#include <cpt/types.hpp>
#include <raylib.h>
#include <tl/expected.hpp>

namespace uil {
    class FontManager final {
    public:
        enum class Result {
            InvalidPath,
            InvalidId,

            Success,
        };

        [[nodiscard]] static bool is_success(Result const& result);

    private:
        std::unordered_map<cpt::usize, Font> m_font{};
        Font m_default_font;
        cpt::usize m_next_id = 1;

    public:
        FontManager();
        FontManager(FontManager const&)                = delete;
        FontManager(FontManager&&) noexcept            = default;
        FontManager& operator=(FontManager const&)     = delete;
        FontManager& operator=(FontManager&&) noexcept = default;
        ~FontManager();

        tl::expected<cpt::usize, Result> load_font(std::filesystem::path const& path);
        Result unload(cpt::usize id);

        Font& get(cpt::usize id);
        Font* get_ptr(cpt::usize id);
    };
}
