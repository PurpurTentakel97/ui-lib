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
        TestElement(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, Color color);

        void render(Context const& context) const override;
    };
}