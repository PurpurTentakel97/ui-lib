//
// Purpur Tentakel
// 07.07.24
//

#include <iostream>
#include <uil/context.hpp>
#include <uil/text.hpp>

namespace uil {
    void Text::align() {

        if (not m_font) { // also checked in update_(). just to be shure because it could be called directly
            return;
        }

        std::cout << "TODO: text.cpp - align() // Need to implement\n"; // @todo remove iostream import
        // @todo implement alignment here
    }

    void Text::break_() {
        auto const extra_breaking = m_breaking or m_font != nullptr;
        if (not extra_breaking) {
            m_draw_text = {
                { Vector2(0.0f, 0.0f), m_raw_text }
            };
            return;
        }

        cpt::usize lhs      = 0;
        cpt::usize rhs      = 0;
        m_draw_text         = DrawText();
        bool next_paragraph = false;

        auto const text_size
                = [size = m_font_size, font = m_font, spacing = m_letter_spacing](std::string const& text) {
                      return MeasureTextEx(*font, text.c_str(), size, spacing);
                  };

        auto const add = [&]() {
            if (m_draw_text.empty()) {
                m_draw_text.emplace_back(Vector2(0.0f, 0.0f), m_raw_text.substr(lhs, rhs - lhs));
            } else {
                auto const last      = m_draw_text.back();
                auto const last_size = text_size(last.second);
                auto const spacing   = next_paragraph ? m_paragraph_spacing : m_line_spacing;
                next_paragraph       = false;

                m_draw_text.emplace_back(Vector2(0.0f, last.first.y + last_size.y + spacing),
                                         m_raw_text.substr(lhs, rhs - lhs));
            }

            if (rhs == std::string::npos) {
                return;
            }

            ++rhs;
            lhs = rhs;
        };


        while (true) {
            auto rhs_temp = m_raw_text.find_first_of('\n', rhs);
            if (rhs_temp != std::string::npos) {
                auto const size = text_size(m_raw_text.substr(lhs, rhs_temp - lhs));
                if (size.x < collider_aligned().width) {
                    rhs = rhs_temp;
                    add();
                    next_paragraph = true;
                    continue;
                }
            }

            rhs_temp = m_raw_text.find_first_of(' ', rhs);

            if (rhs_temp == std::string::npos) {
                rhs = rhs_temp;
                add();
                break;
            }

            auto const size = text_size(m_raw_text.substr(lhs, rhs_temp - lhs));
            if (size.x > collider_aligned().width) {
                auto const lower_rhs = m_raw_text.find_last_of(' ', rhs - 1);
                rhs                  = lower_rhs == std::string::npos ? rhs_temp : lower_rhs;
                add();
            }
            ++rhs;
        }
    }

    Text::Text(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution)
        : UIElement{ relative, alignment, resolution },
          m_font_size{ m_relative_font_size * collider_aligned().height },
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
        return m_letter_spacing;
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

    void Text::set_render_line_collider_debug(bool const draw) {
        m_render_line_collider = draw;
    }

    bool Text::render_line_collider_debug() const {
        return m_render_line_collider;
    }

    void Text::update_text() {
        if (not m_font) {
            m_draw_text = {
                { Vector2(0.0f, 0.0f), m_raw_text }
            };
            return;
        }

        break_();
        align();
    }

    bool Text::check(Context const& context) {
        auto const keep_checking = UIElement::check(context);

        if (m_font != context.font) {
            m_font = context.font;
            update_text();
        }

        return keep_checking;
    }

    bool Text::render(Context const& context) const {
        auto const keep_updating = UIElement::render(context);

        for (auto const& e : m_draw_text) {
            // clang-format off
            DrawTextEx(
                    *(context.font),
                    e.second.c_str(),
                    { collider_aligned().x + e.first.x, collider_aligned().y + e.first.y },
                    m_font_size,
                    m_letter_spacing,
                    m_color
                    );
            // clang-format on

#ifdef _DEBUG
            if (m_render_line_collider) {
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
        return keep_updating;
    }

    void Text::resize(Context const& context) {
        UIElement::resize(context);
        m_font_size = m_relative_font_size * collider_aligned().height;
        update_text();
    }
} // namespace uil
