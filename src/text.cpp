//
// Purpur Tentakel
// 07.07.24
//

#include <uil/text.hpp>

namespace uil {
    Text::Text(Rectangle const relative,
               Alignment const alignment,
               cpt::Vec2_i const resolution,
               float const font_size,
               std::string text)
        : UIElement{ relative, alignment, resolution },
          m_relative_font_size{ font_size },
          m_font_size{ m_relative_font_size * collider_aligned().height },
          m_text{ std::move(text) } { }

    Text::Text(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution, float const font_size)
        : Text{ relative, alignment, resolution, font_size, std::string{} } { }

    void Text::set_text(std::string text) {
        auto temp = std::exchange(m_text, std::move(text));
        on_text_changed.invoke(*this, std::move(temp));
    }

    std::string Text::text() const {
        return m_text;
    }

    void Text::set_relative_font_size(float const size) {
        auto const temp = std::exchange(m_relative_font_size, size);
        m_font_size     = m_relative_font_size * collider_aligned().height;
        on_text_size_changed.invoke(*this, temp);
    }

    float Text::relative_font_size() const {
        return m_relative_font_size;
    }

    void Text::set_absolute_font_size(float const size) {
        m_font_size     = size;
        auto const temp = std::exchange(m_relative_font_size, (collider_aligned().height / m_font_size));
        on_text_size_changed.invoke(*this, temp);
    }

    float Text::absolute_font_size() const {
        return m_relative_font_size;
    }

    void Text::set_spacing(float const spacing) {
        auto const temp = std::exchange(m_spacing, spacing);
        on_spacing_changed.invoke(*this, temp);
    }

    float Text::spacing() const {
        return m_spacing;
    }

    void Text::set_color(Color const color) {
        auto const temp = std::exchange(m_color, color);
        on_color_changed.invoke(*this, temp);
    }

    Color Text::color() const {
        return m_color;
    }

    bool Text::render(Font const* const font) const {
        auto const keep_updating = UIElement::render(font);
        // clang-format off
        DrawTextEx(
                *font,
                m_text.c_str(),
                { collider_aligned().x, collider_aligned().y },
                m_font_size,
                m_spacing,
                m_color
                );
        // clang-format on

        return keep_updating;
    }

    void Text::resize(cpt::Vec2_i const& resolution) {
        UIElement::resize(resolution);
        m_font_size = m_relative_font_size * collider_aligned().height;
    }
} // namespace uil
