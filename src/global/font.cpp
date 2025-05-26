//
// Purpur Tentakel
// 25.05.25
//

#include <ranges>
#include <uil/global/font.hpp>
#include <cpt/log.hpp>
#include <unordered_set>
#include <cpt/files.hpp>

namespace uil {
    bool FontManager::is_success(Result const& result) {
        return result == Result::Success;
    }

    FontManager::FontManager() : m_default_font{ GetFontDefault() } {}

    FontManager::~FontManager() {
        for (const auto& font : m_font | std::views::values) {
            UnloadFont(font);
        }

        cpt::log::info("[[Font Manager]] | all font unloaded");
    }

    tl::expected<cpt::usize, FontManager::Result> FontManager::load(std::filesystem::path const& path) {
        auto const font = LoadFont(cpt::make_absolute_path(path).string().c_str());
        if (not IsFontValid(font)) {
            cpt::log::r_error("[[Font Manager]] | failed to load font from the path '{}'", path.string());
            return tl::unexpected{ Result::InvalidPath };
        }

        auto const id = m_next_id++;
        m_font[id]    = font;
        cpt::log::info("[[Font Manager]] | loaded font with id '{}' from the path '{}'", id, path.string());
        return id;
    }

    FontManager::Result FontManager::unload(cpt::usize const id) {
        if (not m_font.contains(id)) {
            cpt::log::r_error("[[Font Manager]] | failed to unload id '{}'", id);
            return Result::InvalidId;
        }

        UnloadFont(m_font.at(id));
        m_font.erase(id);
        cpt::log::info("[[Font Manager]] | unloaded id '{}'", id);
        return Result::Success;
    }

    Font const& FontManager::get(cpt::usize const id) const {
        if (not m_font.contains(id)) {
            static std::unordered_set<cpt::usize> already_warned{};
            if (already_warned.insert(id).second) {
                cpt::log::r_error("[[Font Manager]] | id '{}' missing", id);
            }
            return m_default_font;
        }

        return m_font.at(id);
    }

    Font const* FontManager::get_ptr(cpt::usize const id) const {
        return &get(id);
    }
}
