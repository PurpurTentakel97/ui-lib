//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include "ui_element.hpp"

namespace uil {
    class Text : public UIElement {
    private:
        float m_relative_font_size;
        float m_font_size;
        Alignment m_text_alignment = Alignment::TopLeft;
        std::string m_text{};
        float m_spacing        = 3.0f;
        Color m_color          = WHITE;

    public:
        Callback<Text&> on_text_size_changed{};
        Callback<Text&> on_text_changed{};
        Callback<Text&> on_spacing_changed{};
        Callback<Text&> on_color_changed{};

        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size);

        void set_text(std::string text);
        [[nodiscard]] std::string text() const;

        void set_relative_font_size(float size);
        [[nodiscard]] float relative_font_size() const;

        void set_absolute_font_size(float size);
        [[nodiscard]] float absolute_font_size() const;

        void set_spacing(float spacing);
        [[nodiscard]] float spacing() const;

        void set_color(Color color);
        [[nodiscard]] Color color() const;

        [[nodiscard]] bool render(Font const* font) const override;
        void resize(cpt::Vec2_i const& resolution) override;
    };
} // namespace uil
