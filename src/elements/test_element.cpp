//
// Purpur Tentakel
// 03.08.24
//

#include <uil/elements/test_element.hpp>

namespace uil {

    TestElement::TestElement(cpt::Vec2_i const resolution,
                             Rectangle const relative,
                             Alignment const alignment,
                             Color const color)
        : UIElement{ resolution, relative, alignment },
          m_color{ color } { }

    void TestElement::render(Context const& context) const {
        UIElement::render(context);

        DrawRectangleRec(collider_aligned(), m_color);
    }
} // namespace uil
