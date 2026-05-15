//
// Purpur Tentakel
// 01.04.25
//

#include <uil/global/app_context.hpp>

namespace uil {
    AppContext& AppContext::instance() {
        static AppContext app_context{};
        return app_context;
    }
    void AppContext::update() {
        m_sound.update();
    }

    sys::InputManager& AppContext::input() {
        return m_input;
    }

    sys::InputManager const& AppContext::input() const {
        return m_input;
    }

    sys::SoundManager& AppContext::sound() {
        return m_sound;
    }

    sys::SoundManager const& AppContext::sound() const {
        return m_sound;
    }

    sys::TextureManager& AppContext::texture() {
        return m_texture;
    }

    sys::TextureManager const& AppContext::texture() const {
        return m_texture;
    }

    sys::ResolutionManager& AppContext::resolution() {
        return m_resolution;
    }

    sys::ResolutionManager const& AppContext::resolution() const {
        return m_resolution;
    }

    sys::FontManager& AppContext::font() {
        return m_font;
    }

    sys::FontManager const& AppContext::font() const {
        return m_font;
    }
} // namespace uil
