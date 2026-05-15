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

    InputManager& AppContext::input() {
        return m_input;
    }

    InputManager const& AppContext::input() const {
        return m_input;
    }


    SoundManager& AppContext::sound() {
        return m_sound;
    }

    SoundManager const& AppContext::sound() const {
        return m_sound;
    }


    TextureManager& AppContext::texture() {
        return m_texture;
    }

    TextureManager const& AppContext::texture() const {
        return m_texture;
    }


    ResolutionManager& AppContext::resolution() {
        return m_resolution;
    }

    ResolutionManager const& AppContext::resolution() const {
        return m_resolution;
    }

    FontManager& AppContext::font() {
        return m_font;
    }

    FontManager const& AppContext::font() const {
        return m_font;
    }

    TooltipManager& AppContext::tooltip_manager() {
        return m_tooltip_manager;
    }

    TooltipManager const& AppContext::tooltip_manager() const {
        return m_tooltip_manager;
    }
} // namespace uil
