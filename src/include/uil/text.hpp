//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include "ui_element.hpp"

namespace uil {
    class Text : public UIElement {
    private:
        std::string m_text{};
        float m_font_size;
        Color m_color = WHITE;

    public:
        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size, std::string text);
        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size);

        void set_text(std::string text);
        [[nodiscard]] std::string text() const;

        void set_color(Color color);
        [[nodiscard]] Color color() const;

        [[nodiscard]] bool render(Font const* font) const override;
    };
} // namespace uil
