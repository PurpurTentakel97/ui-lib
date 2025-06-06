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
        m_focus.update();
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


    AssetManager& AppContext::asset() {
        return m_asset;
    }

    AssetManager const& AppContext::asset() const {
        return m_asset;
    }


    ResolutionManager& AppContext::resolution() {
        return m_resolution;
    }

    ResolutionManager const& AppContext::resolution() const {
        return m_resolution;
    }

    FocusManager& AppContext::focus() {
        return m_focus;
    }
    FocusManager const& AppContext::focus() const {
        return m_focus;
    }

    FontManager& AppContext::font() {
        return m_font;
    }

    FontManager const& AppContext::font() const {
        return m_font;
    }
} // namespace uil
