//
// Purpur Tentakel
// 25.05.25
//

#include <uil/elements/button.hpp>
#include <uil/global/app_context.hpp>
#include <uil/helper/rect.hpp>

namespace uil {
    void Button::update_texture() {
        switch (m_state) {
            case State::Enabled: {
                m_current_texture_id = m_asset_config.enabled_texture_id;
                break;
            }
            case State::Hovered: {
                m_current_texture_id = m_asset_config.hovered_texture_id;
                break;
            }
            case State::Pressed: {
                m_current_texture_id = m_asset_config.pressed_texture_id;
                break;
            }
            case State::Disabled: {
                m_current_texture_id = m_asset_config.disabled_texture_id;
                break;
            }
        }
    }

    ButtonAssetConfig const& Button::asset_config() const {
        return m_asset_config;
    }
    void Button::set_asset_config(ButtonAssetConfig const& config) {
        m_asset_config = config;
        update_texture();
    }

    void Button::enable() {
        m_state = State::Enabled;
        update_texture();
        on_enabled.invoke(*this);
    }
    void Button::disable() {
        m_state = State::Disabled;
        update_texture();
        on_disabled.invoke(*this);
    }
    bool Button::is_disabled() const {
        return m_state == State::Disabled;
    }

    bool Button::handle_input(UpdateContext const& context) {
        auto const keep_handle_input = UIElement::handle_input(context);

        auto const& input = AppContext::instance().input();
        auto& sound       = AppContext::instance().sound();

        auto const handle_state_switch = [&](auto const& state,
                                             cpt::usize const sound_id,
                                             std::vector<cpt::Callback<Button&>> const& callbacks) {
            m_state = state;
            sound.play_sound(sound_id);
            update_texture();

            for (auto const& c : callbacks) {
                c.invoke(*this);
            }
        };

        switch (m_state) {
            case State::Enabled: {
                if (hovered()) {
                    handle_state_switch(State::Hovered, m_asset_config.hovered_on_sound_id, {});
                    break;
                }
                if (is_focused() and input.is_down(InputManager::Pattern::Accept)) {
                    handle_state_switch(State::Pressed, m_asset_config.pressed_sound_id, { on_pressed });
                    break;
                }
                break;
            }

            case State::Hovered: {
                if (!hovered()) {
                    handle_state_switch(State::Enabled, m_asset_config.hovered_off_sound_id, {});
                    break;
                }

                if (input.is_down(Mouse::MOUSE_BUTTON_LEFT)) {
                    handle_state_switch(State::Pressed, m_asset_config.pressed_sound_id, { on_pressed });
                    break;
                }

                if (is_focused() and input.is_down(InputManager::Pattern::Accept)) {
                    handle_state_switch(State::Pressed, m_asset_config.pressed_sound_id, { on_pressed });
                    break;
                }
                break;
            }
            case State::Pressed: {
                auto const mouse_input    = input.is_down(Mouse::MOUSE_BUTTON_LEFT);
                auto const keyboard_input = is_focused() && input.is_down(InputManager::Pattern::Accept);
                if (mouse_input or keyboard_input) {
                    break;
                }

                auto const next_state = hovered() ? State::Hovered : State::Enabled;
                if (input.is_released(InputManager::Pattern::Accept)) {
                    handle_state_switch(next_state, m_asset_config.clicked_sound_id, { on_clicked, on_released });
                    break;
                }

                if (input.is_released(Mouse::MOUSE_BUTTON_LEFT)) {
                    if (hovered()) {
                        handle_state_switch(next_state, m_asset_config.clicked_sound_id, { on_clicked, on_released });
                    } else {
                        handle_state_switch(next_state, m_asset_config.released_sound_id, { on_released });
                    }
                    break;
                }

                break;
            }
            case State::Disabled: {
                if (hovered() and input.is_pressed(Mouse::MOUSE_BUTTON_LEFT)) {
                    sound.play_sound(m_asset_config.disabled_sound_id);
                    break;
                }
                if (is_focused() and input.is_pressed(InputManager::Pattern::Accept)) {
                    sound.play_sound(m_asset_config.disabled_sound_id);
                    break;
                }
                break;
            }
        }

        return keep_handle_input;
    }

    void Button::render() const {
        auto const texture = AppContext::instance().texture().get(m_current_texture_id);
        DrawTexturePro(texture, rect_from_texture(texture), m_collider, { 0.0f, 0.0f }, 0.0f, WHITE);
        UIElement::render();
    }
} // namespace uil
