//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include "system/tooltip_manager.hpp"
#include <system/font.hpp>
#include <system/input.hpp>
#include <system/resolution.hpp>
#include <system/sound.hpp>
#include <system/texture.hpp>

namespace uil {
    class Window;
}

namespace uil {

    class AppContext final {
    private:
        InputManager m_input{};
        SoundManager m_sound{};
        TextureManager m_texture{};
        ResolutionManager m_resolution{};
        FontManager m_font{};
        TooltipManager m_tooltip_manager{};

    public:
        AppContext()                             = default;
        AppContext(AppContext const&)            = delete;
        AppContext(AppContext&&)                 = delete;
        AppContext& operator=(AppContext const&) = delete;
        AppContext& operator=(AppContext&&)      = delete;
        ~AppContext()                            = default;

        [[nodiscard]] static AppContext& instance();
        void update();

        [[nodiscard]] InputManager& input();
        [[nodiscard]] InputManager const& input() const;

        [[nodiscard]] SoundManager& sound();
        [[nodiscard]] SoundManager const& sound() const;

        [[nodiscard]] TextureManager& texture();
        [[nodiscard]] TextureManager const& texture() const;

        [[nodiscard]] ResolutionManager& resolution();
        [[nodiscard]] ResolutionManager const& resolution() const;

        [[nodiscard]] FontManager& font();
        [[nodiscard]] FontManager const& font() const;

        [[nodiscard]] TooltipManager& tooltip_manager();
        [[nodiscard]] TooltipManager const& tooltip_manager() const;
    };
} // namespace uil
