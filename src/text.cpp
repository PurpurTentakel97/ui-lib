//
// Purpur Tentakel
// 07.07.24
//

#include <iostream>
#include <uil/context.hpp>
#include <uil/text.hpp>

namespace uil {
    void Text::update_() {
        m_aligned_text = m_raw_text;

        if (not m_font) {
            return;
        }

        break_();
        align();
    }

    void Text::align() {

        if (not m_font) { // also checked in update_(). just to be shure because it could be called directly
            return;
        }

        std::cout << "TODO: text.cpp - align() // Need to implement\n"; // @todo remove iostream import
        // @todo implement alignment here
    }

    void Text::break_() {

        if (not m_font) { // also checked in update_(). just to be shure because it could be called directly
            return;
        }

        if (not m_breaking) {
            return;
        }
        std::cout << "TODO: text.cpp - break_() // Need to implement\n"; // @todo remove iostream import
        // @todo implement break here
    }

    Text::Text(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution, float const font_size)
        : UIElement{ relative, alignment, resolution },
          m_relative_font_size{ font_size },
          m_font_size{ m_relative_font_size * collider_aligned().height } { }

    void Text::set_text(std::string text) {
        m_raw_text = std::move(text);
        update_();
        on_text_changed.invoke(*this);
    }

    std::string Text::text() const {
        return m_raw_text;
    }

    void Text::set_relative_font_size(float const size) {
        m_relative_font_size = size;
        m_font_size          = m_relative_font_size * collider_aligned().height;
        on_text_size_changed.invoke(*this);
    }

    float Text::relative_font_size() const {
        return m_relative_font_size;
    }

    void Text::set_absolute_font_size(float const size) {
        m_font_size          = size;
        m_relative_font_size = collider_aligned().height / m_font_size;
        on_text_size_changed.invoke(*this);
    }

    float Text::absolute_font_size() const {
        return m_relative_font_size;
    }

    void Text::set_spacing(float const spacing) {
        m_spacing = spacing;
        on_spacing_changed.invoke(*this);
    }

    float Text::spacing() const {
        return m_spacing;
    }

    void Text::set_color(Color const color) {
        m_color = color;
        on_color_changed.invoke(*this);
    }

    Color Text::color() const {
        return m_color;
    }

    void Text::set_text_alignment(Alignment const alignment) {
        m_text_alignment = alignment;
        update_();
    }

    Alignment Text::text_alignment() const {
        return m_text_alignment;
    }

    void Text::set_breaking(bool const breaking) {
        m_breaking = breaking;
        update_();
    }

    bool Text::breaking() const {
        return m_breaking;
    }

    bool Text::check(Context const& context) {
        auto const keep_checking = UIElement::check(context);

        if (m_font != context.font) {
            m_font = context.font;
            update_();
        }

        return keep_checking;
    }

    bool Text::render(Context const& context) const {
        auto const keep_updating = UIElement::render(context);
        // clang-format off
        DrawTextEx(
                *(context.font),
                m_aligned_text.c_str(),
                { collider_aligned().x, collider_aligned().y },
                m_font_size,
                m_spacing,
                m_color
                );
        // clang-format on

        return keep_updating;
    }

    void Text::resize(Context const& context) {
        UIElement::resize(context);
        m_font_size = m_relative_font_size * collider_aligned().height;
    }
} // namespace uil
