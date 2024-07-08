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
          m_font_size{ font_size * collider().height },
          m_text{ std::move(text) } { }

    Text::Text(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution, float const font_size)
        : Text{ relative, alignment, resolution, font_size, std::string{} } { }

    Text& Text::set_text(std::string text) {
        m_text = std::move(text);
        return *this;
    }

    std::string Text::text() const {
        return m_text;
    }

    Text& Text::set_spacing(float const spacing) {
        m_spacing = spacing;
        return *this;
    }

    float Text::spacing() const {
        return m_spacing;
    }

    Text& Text::set_color(Color const color) {
        m_color = color;
        return *this;
    }

    Color Text::color() const {
        return m_color;
    }

    Text& Text::set_render_collider(bool const render_collider) {
        m_render_collider = render_collider;
        return *this;
    }

    bool Text::render_collider() const {
        return m_render_collider;
    }

    bool Text::render(Font const* const font) const {
        DrawTextEx(*font, m_text.c_str(), { collider().x, collider().y }, m_font_size, m_spacing, m_color);

        if (m_render_collider) {
            DrawRectangleLinesEx(collider(), 2.0f, WHITE);
        }

        return true;
    }
} // namespace uil
