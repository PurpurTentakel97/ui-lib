//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <uil/global/input.hpp>
#include <uil/global/sound.hpp>
#include <uil/global/asset.hpp>
#include <uil/global/resolution.hpp>
#include <uil/global/focus.hpp>
#include <uil/global/font.hpp>

namespace uil {
    class Window;
}

namespace uil {

    class AppContext final {
    private:
        InputManager m_input{};
        SoundManager m_sound{};
        AssetManager m_asset{};
        ResolutionManager m_resolution{};
        FontManager m_font{};
        FocusManager m_focus{};

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

        [[nodiscard]] AssetManager& asset();
        [[nodiscard]] AssetManager const& asset() const;

        [[nodiscard]] ResolutionManager& resolution();
        [[nodiscard]] ResolutionManager const& resolution() const;

        [[nodiscard]] FocusManager& focus();
        [[nodiscard]] FocusManager const& focus() const;

        [[nodiscard]] FontManager& font();
        [[nodiscard]] FontManager const& font() const;
    };
} // namespace uil
