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
          m_text{ std::move(text) },
          m_font_size{ font_size * collider().height } { }

    Text::Text(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution, float const font_size)
        : Text{ relative, alignment, resolution, font_size, std::string{} } { }

    void Text::set_text(std::string text) {
        m_text = std::move(text);
    }

    std::string Text::text() const {
        return m_text;
    }

    void Text::set_color(Color const color) {
        m_color = color;
    }

    Color Text::color() const {
        return m_color;
    }

    bool Text::render(Font const* const font) const {
        DrawTextEx(*font, m_text.c_str(), { collider().x, collider().y }, m_font_size, 2.0f, m_color);

        DrawRectangleLinesEx(collider(), 2.0f, WHITE);

        return true;
    }
} // namespace uil
