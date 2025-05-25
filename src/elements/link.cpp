//
// Purpur Tentakel
// 27.07.24
//

#include <uil/update_context.hpp>
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

    bool Link::handle_input(UpdateContext const& context) {
        auto const keep_checking = Text::handle_input(context);

        if (not hovered()) {
            return keep_checking;
        }

        on_hover.invoke(*this);

        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        if (not IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return false;
        }

        if (not m_link.empty()) {
            OpenURL(m_link.c_str());
        }

        on_click.invoke(*this);

        if (not m_clicked) {
            m_clicked = true;
            on_first_click.invoke(*this);
        }

        return false;
    }

    void Link::render(UpdateContext const& context) const {
        // NOLINTNEXTLINE
        UIElement::render(context);

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
    }
} // namespace uil
