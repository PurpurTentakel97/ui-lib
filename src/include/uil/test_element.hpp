//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include "ui_element.hpp"

namespace uil {
    class TestElement final : public UIElement {
    private:
        bool m_rectangle;
    public:
        TestElement(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, bool rectangle);

        [[nodiscard]] bool render() const override;
    };
}
