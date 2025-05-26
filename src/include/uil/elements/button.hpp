//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <cpt/types.hpp>
#include <uil/element.hpp>

namespace uil {
    struct ButtonAssetConfig final {
        cpt::usize disabled_texture_id = 0;
        cpt::usize hovered_texture_id  = 0;
        cpt::usize pressed_texture_id  = 0;
        cpt::usize enabled_texture_id  = 0;
        cpt::usize focused_texture_id  = 0;

        cpt::usize font_id = 0;

        cpt::usize hovered_on_sound_id  = 0;
        cpt::usize hovered_off_sound_id = 0;
        cpt::usize pressed_sound_id     = 0;
        cpt::usize released_sound_id    = 0;
    };

    class Button : public UIElement {
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

    public:
        using UIElement::UIElement;

        [[nodiscard]] ButtonAssetConfig const& asset_config() const;
        void set_asset_config(ButtonAssetConfig const& config);

        [[nodiscard]] State state() const;
        void set_state(State state);

        [[nodiscard]] bool handle_input(UpdateContext const& context) override;
        [[nodiscard]] bool update(UpdateContext const& context) override;
        void render() const override;
    };
} // namespace uil
