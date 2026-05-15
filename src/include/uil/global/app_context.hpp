//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <system/manager/font.hpp>
#include <system/manager/input.hpp>
#include <system/manager/resolution.hpp>
#include <system/manager/sound.hpp>
#include <system/manager/texture.hpp>

namespace uil {
    class Window;
}

namespace uil {

    class AppContext final {
    private:
        sys::InputManager m_input{};
        sys::SoundManager m_sound{};
        sys::TextureManager m_texture{};
        sys::ResolutionManager m_resolution{};
        sys::FontManager m_font{};

    public:
        AppContext()                             = default;
        AppContext(AppContext const&)            = delete;
        AppContext(AppContext&&)                 = delete;
        AppContext& operator=(AppContext const&) = delete;
        AppContext& operator=(AppContext&&)      = delete;
        ~AppContext()                            = default;

        [[nodiscard]] static AppContext& instance();
        void update();

        [[nodiscard]] sys::InputManager& input();
        [[nodiscard]] sys::InputManager const& input() const;

        [[nodiscard]] sys::SoundManager& sound();
        [[nodiscard]] sys::SoundManager const& sound() const;

        [[nodiscard]] sys::TextureManager& texture();
        [[nodiscard]] sys::TextureManager const& texture() const;

        [[nodiscard]] sys::ResolutionManager& resolution();
        [[nodiscard]] sys::ResolutionManager const& resolution() const;

        [[nodiscard]] sys::FontManager& font();
        [[nodiscard]] sys::FontManager const& font() const;
    };
} // namespace uil
