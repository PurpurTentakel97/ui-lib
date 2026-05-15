//
// Purpur Tentakel
// 15.05.26
//

#include "uil/global/app_context.hpp"
#include <raylib.h>
#include <uil/elements/tooltip.hpp>
#include <uil/global/update_context.hpp>

namespace uil {
    void Tooltip::render(Vector2 const& position) const {
        DrawTextEx(AppContext::instance().font().get(m_font_id), m_text.c_str(), position, 16, 0, WHITE);
    }

    Tooltip::Tooltip(std::string text, cpt::usize const font_id) : m_text{ std::move(text) }, m_font_id{ font_id } { }

    void Tooltip::set_hover_delay(double const delay) {
        m_hover_delay = delay;
    }

    double Tooltip::hover_delay() const {
        return m_hover_delay;
    }

    bool Tooltip::handle_input(UpdateContext const& context, Rectangle const& collider) {
        if (CheckCollisionPointRec(context.mouse_position, collider)) {
            if (not m_hovered) {
                m_hovered            = true;
                m_hovered_start_time = GetTime();
            }
            if (GetTime() - m_hovered_start_time <= m_hover_delay) {
                AppContext::instance().tooltip_manager().push(this);
            }
        } else {
            m_hovered = false;
        }
        return true;
    }

} // namespace uil
