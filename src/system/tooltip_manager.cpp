//
// Purpur Tentakel
// 15.05.26
//

#include <raylib.h>
#include <system/tooltip_manager.hpp>
#include <uil/elements/tooltip.hpp>
namespace uil {
    struct TooltipRenderPosition {
        Tooltip* tooltip;
        Vector2 position;
    };

    std::vector<TooltipManager::TooltipRenderPosition> TooltipManager::get_render_positions() const {
        std::vector<TooltipRenderPosition> positions{};
        auto const mouse_position = GetMousePosition();
        auto next_position
                = Vector2(mouse_position.x + m_absolute_mouse_offset, mouse_position.y + m_absolute_mouse_offset);

        for (auto const& tooltip : m_tooltips) {
            positions.push_back({ tooltip, next_position });
        }

        return positions;
    }

    void TooltipManager::push(Tooltip* tooltip) {
        m_tooltips.push_back(tooltip);
    }

    void TooltipManager::render() {
        if (m_tooltips.empty()) {
            return;
        }

        auto const positions = get_render_positions(m_tooltips);
        for (auto const& [tooltip, position] : positions) {
            tooltip->render(position);
        }

        m_tooltips.clear();
    }

    void TooltipManager::set_alignment(Alignment const alignment) {
        m_alignment = alignment;
    }

    Alignment TooltipManager::alignment() const {
        return m_alignment;
    }

    void TooltipManager::set_absolute_mouse_offset(float const offset) {
        m_absolute_mouse_offset = offset;
    }

    float TooltipManager::absolute_mouse_offset() const {
        return m_absolute_mouse_offset;
    }

    void TooltipManager::set_absolute_gap(float const gap) {
        m_absolute_gap = gap;
    }

    float TooltipManager::absolute_gap() const {
        return m_absolute_gap;
    }
} // namespace uil
