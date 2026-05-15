//
// Purpur Tentakel
// 15.05.26
//

#pragma once
#include <uil/global/alignment.hpp>
#include <vector>

namespace uil {
    class Tooltip;
}

namespace uil {
    class TooltipManager final {
    public:
        friend class Tooltip;

    private:
        struct TooltipRenderPosition {
            Tooltip* tooltip;
            Vector2 position;
        };

        std::vector<Tooltip*> m_tooltips{};
        Alignment m_alignment         = Alignment::BottomRight;
        float m_absolute_mouse_offset = 10.0f;
        float m_absolute_gap = 0.2f;

        [[nodiscard]] std::vector<TooltipRenderPosition> get_render_positions() const;

        void push(Tooltip* tooltip);

    public:
        void render();

        void set_alignment(Alignment alignment);
        [[nodiscard]] Alignment alignment() const;

        void set_absolute_mouse_offset(float offset);
        [[nodiscard]] float absolute_mouse_offset() const;

        void set_absolute_gap(float gap);
        [[nodiscard]] float absolute_gap() const;
    };
} // namespace uil
