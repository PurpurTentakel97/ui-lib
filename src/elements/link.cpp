//
// Purpur Tentakel
// 27.07.24
//

#include "uil/context.hpp"
#include <uil/elements/link.hpp>

namespace uil {
    void Link::set_color_clicked(Color const color) {
        m_color_clicked = color;
    }

    Color Link::color_clicked() const {
        return m_color_clicked;
    }

    void Link::set_link(std::string link) {
        m_link = std::move(link);
    }

    std::string Link::link() const {
        return m_link;
    }

    void Link::set_clicked(bool const clicked) {
        m_clicked = clicked;
    }

    bool Link::clicked() const {
        return m_clicked;
    }

    void Link::set_render_hover(bool const render_hover) {
        m_render_hover = render_hover;
    }

    bool Link::render_hover() const {
        return m_render_hover;
    }

    bool Link::check(Context const& context) {
        auto const keep_checking = Text::check(context);

        if (m_link.empty()) {
            return keep_checking;
        }

        if (not hovered()) {
            return keep_checking;
        }

        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        if (not IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return false;
        }

        m_clicked = true;
        OpenURL(m_link.c_str());
        return false;
    }

    bool Link::render(Context const& context) const {
        // NOLINTNEXTLINE
        auto const keep_rendering = UIElement::render(context);

        render_text(context, m_clicked ? m_color_clicked : color());

        if (hovered() and m_render_hover) {
            auto const single_size = [&](std::string const& text) {
                return MeasureTextEx(*(context.font), text.c_str(), absolute_font_size(), absolute_letter_spacing());
            };

            for (auto const& t : draw_text()) {
                auto const size = single_size(t.second);
                auto const pos  = Vector2(collider_aligned().x + t.first.x, collider_aligned().y + t.first.y + size.y);
                // clang-format off
                DrawLineEx(
                    pos,
                    Vector2(pos.x + size.x, pos.y),
                    1.0f,
                    m_clicked ? m_color_clicked : color()
                );
                // clang-format on
            }
        }

        return keep_rendering;
    }
} // namespace uil
