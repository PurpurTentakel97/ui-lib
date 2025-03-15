//
// Purpur Tentakel
// 07.07.24
//

#include <uil/context.hpp>
#include <uil/elements/text.hpp>

namespace uil {
    void Text::align() {

        if (not m_font) { // also checked in update_(). just to be sure because it could be called directly
            return;
        }

        auto const single_line_size = [&](std::string const& text) {
            return MeasureTextEx(*m_font, text.c_str(), m_font_size, m_letter_spacing);
        };

        auto const total_height = [&]() {
            if (m_draw_text.empty()) {
                return 0.0f;
            }
            if (m_draw_text.size() == 1) {
                return single_line_size(m_draw_text.front().second).y;
            }
            return m_draw_text.back().first.y - m_draw_text.front().first.y
                 + single_line_size(m_draw_text.back().second).y;
        }();

        auto const height = [&](VerticalAlignment const alignment) {
            if (alignment == VerticalAlignment::Top) {
                return;
            }
            auto const offset = (collider_aligned().height - total_height);
            for (auto& t : m_draw_text) {
                if (alignment == VerticalAlignment::Mid) {
                    t.first.y += offset / 2.0f;
                    continue;
                }
                t.first.y += offset;
            }
        };
        auto const width = [&](HorizontalAlignment const alignment) {
            if (alignment == HorizontalAlignment::Left) {
                return;
            }
            for (auto& t : m_draw_text) {
                auto const length = single_line_size(t.second).x;
                auto const offset = (collider_aligned().width - length);
                if (alignment == HorizontalAlignment::Mid) {
                    t.first.x += offset / 2.0f;
                    continue;
                }
                t.first.x += offset;
            }
        };

        height(to_vertical_alignment(m_text_alignment));
        width(to_horizontal_alignment(m_text_alignment));
    }

    void Text::break_() {
        auto const extra_breaking = m_breaking and m_font != nullptr;
        if (not extra_breaking) {
            m_draw_text = {
                { Vector2(0.0f, 0.0f), m_raw_text }
            };
            return;
        }

        cpt::usize lhs              = 0;
        cpt::usize rhs              = 0;
        m_draw_text                 = DrawText{};
        auto next_paragraph_spacing = false;

        auto const calc_text_size
                = [size = m_font_size, font = m_font, spacing = m_letter_spacing](std::string const& line) {
                      return MeasureTextEx(*font, line.c_str(), size, spacing);
                  };

        auto const calc_text_size_by_offset = [calc_text_size,
                                               size    = m_font_size,
                                               font    = m_font,
                                               spacing = m_letter_spacing,
                                               &lhs,
                                               text = m_raw_text](size_t const rhs) {
            auto const& line = text.substr(lhs, rhs - lhs);
            return calc_text_size(line);
        };


        auto const next = [&rhs, text = m_raw_text](char const c) { return text.find_first_of(c, rhs + 1); };

        auto const add = [&, draw_array = &m_draw_text, text = &m_raw_text](size_t const temp_rhs) {
            auto const line = [&]() {
                if (temp_rhs == 0) {
                    return text->substr(lhs);
                }
                return text->substr(lhs, temp_rhs - lhs);
            }();

            if (draw_array->empty()) {
                draw_array->emplace_back(Vector2(0.0f, 0.0f), line);
            } else {
                auto const& previous   = draw_array->back();
                auto const size        = calc_text_size(previous.second);
                auto const offset      = next_paragraph_spacing ? m_paragraph_spacing : m_line_spacing;
                next_paragraph_spacing = false;
                draw_array->emplace_back(Vector2{ 0.0f, previous.first.y + size.y + offset }, line);
            }
            rhs = temp_rhs + 1; // promote to strip first character (whitespace or \n) in next line.
            lhs = rhs;
        };

        while (true) {
            auto temp_rhs = next('\n');
            if (auto const found_n = temp_rhs != std::string::npos; found_n) {
                auto const line_dimensions = calc_text_size_by_offset(temp_rhs);
                if (line_dimensions.x < collider().width) {
                    add(temp_rhs);
                    next_paragraph_spacing = true;
                    continue;
                }
            }

            temp_rhs = next(' ');
            if (auto const found_n_pos = temp_rhs == std::string::npos; found_n_pos) {
                auto const line            = m_raw_text.substr(lhs);
                auto const line_dimensions = calc_text_size(line);
                if (line_dimensions.x < collider().width) {
                    add(0);
                    break;
                }
            }

            auto const line_dimensions = calc_text_size_by_offset(temp_rhs);
            if (line_dimensions.x < collider().width) {
                rhs = temp_rhs;
                continue;
            }

            if (lhs == rhs) {
                add(temp_rhs);
                continue;
            }

            add(rhs);
        }
    }

    void Text::render_text(Context const& context, Color const color) const {

        for (auto const& e : m_draw_text) {
            // clang-format off
            DrawTextEx(
                    *(context.font),
                    e.second.c_str(),
                    { collider_aligned().x + e.first.x, collider_aligned().y + e.first.y },
                    m_font_size,
                    m_letter_spacing,
                    color
                    );
            // clang-format on

#ifndef NDEBUG
            if (m_render_line_collider_debug) {
                auto const text_size = [size = m_font_size, font = context.font, spacing = m_letter_spacing](
                                               std::string const& text) -> Vector2 {
                    return MeasureTextEx(*font, text.c_str(), size, spacing);
                }(e.second);

                DrawRectangleLines(static_cast<int>(collider_aligned().x + e.first.x),
                                   static_cast<int>(collider_aligned().y + e.first.y),
                                   static_cast<int>(text_size.x),
                                   static_cast<int>(text_size.y),
                                   WHITE);
            }
#endif
        }
    }

    Text::DrawText Text::draw_text() const {
        return m_draw_text;
    }

    float Text::absolute_font_size() const {
        return m_font_size;
    }

    float Text::absolute_letter_spacing() const {
        return m_letter_spacing;
    }

    float Text::absolute_line_spacing() const {
        return m_line_spacing;
    }

    float Text::absolute_paragraph_spacing() const {
        return m_paragraph_spacing;
    }

    Text::Text(cpt::Vec2_i const resolution, Rectangle const relative, Alignment const alignment)
        : UIElement{ resolution, relative, alignment },
          m_font_size{ m_relative_font_size * static_cast<float>(resolution.y) },
          m_letter_spacing{ static_cast<float>(resolution.x) * m_relative_letter_spacing },
          m_line_spacing{ static_cast<float>(resolution.y) * m_relative_line_spacing },
          m_paragraph_spacing{ static_cast<float>(resolution.y) * m_relative_paragraph_spacing } { }

    void Text::set_text(std::string text) {
        auto const old = std::exchange(m_raw_text, std::move(text));
        on_text_changed.invoke(*this, m_raw_text, old);
    }

    std::string Text::text() const {
        return m_raw_text;
    }

    void Text::set_font_size(float const size) {
        auto const old = std::exchange(m_relative_font_size, size);
        m_font_size    = m_relative_font_size * static_cast<float>(resolution().y);
        on_text_size_changed.invoke(*this, m_relative_font_size, old);
    }

    float Text::font_size() const {
        return m_relative_font_size;
    }

    void Text::set_letter_spacing(float const spacing) {
        auto const old   = std::exchange(m_relative_line_spacing, spacing);
        m_letter_spacing = static_cast<float>(resolution().x) * m_relative_letter_spacing;
        on_letter_spacing_changed.invoke(*this, m_relative_letter_spacing, old);
    }

    float Text::letter_spacing() const {
        return m_relative_letter_spacing;
    }

    void Text::set_line_spacing(float const spacing) {
        auto const old = std::exchange(m_relative_line_spacing, spacing);
        m_line_spacing = static_cast<float>(resolution().y) * m_relative_line_spacing;
        on_line_spacing_chanced.invoke(*this, m_relative_line_spacing, old);
    }

    float Text::line_spacing() const {
        return m_relative_line_spacing;
    }

    void Text::set_paragraph_spacing(float const spacing) {
        auto const old      = std::exchange(m_relative_paragraph_spacing, spacing);
        m_paragraph_spacing = static_cast<float>(resolution().y) * m_relative_paragraph_spacing;
        on_paragraph_spacing_chanced.invoke(*this, m_relative_paragraph_spacing, old);
    }

    float Text::paragraph_spacing() const {
        return m_relative_paragraph_spacing;
    }

    void Text::set_color(Color const color) {
        auto const old = std::exchange(m_color, color);
        on_color_changed.invoke(*this, m_color, old);
    }

    Color Text::color() const {
        return m_color;
    }

    void Text::set_text_alignment(Alignment const alignment) {
        auto const old = std::exchange(m_text_alignment, alignment);
        on_text_alignment_chanced.invoke(*this, m_text_alignment, old);
    }

    Alignment Text::text_alignment() const {
        return m_text_alignment;
    }

    void Text::set_breaking(bool const breaking) {
        auto const old = std::exchange(m_breaking, breaking);
        on_breaking_chanced.invoke(*this, m_breaking, old);
    }

    bool Text::breaking() const {
        return m_breaking;
    }

    void Text::set_render_line_collider_debug([[maybe_unused]] bool const draw) {
#ifndef NDEBUG
        m_render_line_collider_debug = draw;
#endif
    }

    bool Text::render_line_collider_debug() const {
#ifndef NDEBUG
        return m_render_line_collider_debug;
#else
        return false;
#endif
    }

    void Text::update_text() {
        if (not m_font) {
            m_draw_text = {
                { Vector2(0.0f, 0.0f), m_raw_text }
            };
            on_draw_text_updated.invoke(*this);
            return;
        }

        break_();
        align();
        on_draw_text_updated.invoke(*this);
    }

    bool Text::handle_input(Context const& context) {
        auto const keep_checking = UIElement::handle_input(context);

        if (m_font != context.font) {
            m_font = context.font;
            update_text();
        }

        return keep_checking;
    }

    void Text::render(Context const& context) const {
        UIElement::render(context);

        render_text(context, m_color);
    }

    void Text::resize(Context const& context) {
        UIElement::resize(context);
        m_font_size         = m_relative_font_size * static_cast<float>(context.resolution.y);
        m_letter_spacing    = m_relative_letter_spacing * static_cast<float>(context.resolution.x);
        m_line_spacing      = m_relative_line_spacing * static_cast<float>(context.resolution.y);
        m_paragraph_spacing = m_relative_paragraph_spacing * static_cast<float>(context.resolution.y);
        update_text();
    }
} // namespace uil
