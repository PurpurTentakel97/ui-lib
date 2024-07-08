//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include "ui_element.hpp"

namespace uil {
    class Text : public UIElement {
    private:
        float m_font_size;
        std::string m_text{};
        float m_spacing        = 3.0f;
        Color m_color          = WHITE;
        bool m_render_collider = false;

    public:
        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size, std::string text);
        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size);

        Text& set_text(std::string text) &;
        Text set_text(std::string text) &&;
        [[nodiscard]] std::string text() const;

        Text& set_spacing(float spacing) &;
        Text set_spacing(float spacing) &&;
        [[nodiscard]] float spacing() const;

        Text& set_color(Color color) &;
        Text set_color(Color color) &&;
        [[nodiscard]] Color color() const;

        Text& set_render_collider(bool render_collider) &;
        Text set_render_collider(bool render_collider) &&;
        [[nodiscard]] bool render_collider() const;

        [[nodiscard]] bool render(Font const* font) const override;
    };
} // namespace uil
