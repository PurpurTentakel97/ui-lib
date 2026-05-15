//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <uil/global/element.hpp>
#include <cpt/callback.hpp>
#include <cpt/types.hpp>
#include <uil/focus_element.hpp>

namespace uil {
    struct ButtonAssetConfig final {
        cpt::usize disabled_texture_id = 0;
        cpt::usize hovered_texture_id  = 0;
        cpt::usize pressed_texture_id  = 0;
        cpt::usize enabled_texture_id  = 0;

        cpt::usize hovered_on_sound_id  = 0;
        cpt::usize hovered_off_sound_id = 0;
        cpt::usize pressed_sound_id     = 0;
        cpt::usize released_sound_id    = 0;
        cpt::usize clicked_sound_id     = 0;
        cpt::usize disabled_sound_id    = 0;
    };

    class Button : public UIElement, public FocusElement {
    public:
        enum class State {
            Enabled,
            Hovered,
            Pressed,
            Disabled,
        };

    private:
        ButtonAssetConfig m_asset_config{};
        State m_state{ State::Enabled };
        cpt::usize m_current_texture_id{ 0 };

        void update_texture();

    public:
        using UIElement::UIElement;

        cpt::Callback<Button&> on_clicked{};
        cpt::Callback<Button&> on_pressed{};
        cpt::Callback<Button&> on_released{};
        cpt::Callback<Button&> on_disabled{};
        cpt::Callback<Button&> on_enabled{};

        [[nodiscard]] ButtonAssetConfig const& asset_config() const;
        void set_asset_config(ButtonAssetConfig const& config);

        void enable();
        void disable();
        [[nodiscard]] bool is_disabled() const;

        [[nodiscard]] bool handle_input(UpdateContext const& context) override;
        void render() const override;
    };
} // namespace uil
