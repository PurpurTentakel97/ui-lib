//
// Purpur Tentakel
// 25.05.25
//

#include <uil/elements/button.hpp>
#include <uil/global/app_context.hpp>
#include <uil/helper/rect.hpp>

namespace uil {
    ButtonAssetConfig const& Button::asset_config() const {
        return m_asset_config;
    }

    void Button::set_asset_config(ButtonAssetConfig const& config) {
        m_asset_config = config;
    }

    Button::State Button::state() const {
        return m_state;
    }

    void Button::set_state(State const state) {
        m_state = state;
    }

    void Button::render() const {
        auto const texture = AppContext::instance().asset().get(m_current_texture_id);
        DrawTexturePro(texture, rect_from_texture(texture), m_collider, { 0.0f, 0.0f }, 0.0f, BLANK);
        UIElement::render();
    }
} // namespace uil
