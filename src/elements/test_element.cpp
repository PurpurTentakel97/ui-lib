//
// Purpur Tentakel
// 03.08.24
//

#include <uil/elements/test_element.hpp>

namespace uil {

    TestElement::TestElement(Rectangle const relative,
                             Alignment const alignment,
                             cpt::Vec2_i const resolution,
                             Color const color)
        : UIElement{ relative, alignment, resolution },
          m_color{ color } { }

    void TestElement::render(Context const& context) const {
        UIElement::render(context);

        DrawRectangleRec(collider_aligned(), m_color);
    }
} // namespace uil
