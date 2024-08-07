//
// Purpur Tentakel
// 03.08.24
//

#pragma once

#include <uil/element.hpp>

namespace uil {
    class TestElement final : public UIElement {
    private:
        Color m_color;

    public:
        TestElement(cpt::Vec2_i resolution, Rectangle relative, Alignment alignment, Color color);

        void render(Context const& context) const override;
    };
} // namespace uil
