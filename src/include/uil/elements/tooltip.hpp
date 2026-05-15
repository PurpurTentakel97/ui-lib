//
// Purpur Tentakel
// 15.05.26
//

#pragma once
#include <cpt/types.hpp>
#include <string>

struct Rectangle;
struct Vector2;
namespace uil {
    struct UpdateContext;
};

namespace uil {
    class Tooltip {
    public:
        friend class TooltipManager;

    private:
        std::string m_text; // TODO: replace with text element
        cpt::usize m_font_id;
        double m_hover_delay        = 0.0;
        bool m_hovered              = false;
        double m_hovered_start_time = 0;

        void render(Vector2 const& position) const;

    public:
        Tooltip(std::string text, cpt::usize font_id);
        virtual ~Tooltip() = default;

        void set_hover_delay(double delay);
        [[nodiscard]] double hover_delay() const;

        [[nodiscard]] virtual bool handle_input(UpdateContext const& context, Rectangle const& collider);
    };
} // namespace uil
