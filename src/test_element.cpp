//
// Purpur Tentakel
// 06.07.24
//

#include <uil/test_element.hpp>

namespace uil {
    TestElement::TestElement(Rectangle const relative,
                             Alignment const alignment,
                             cpt::Vec2_i const resolution,
                             bool const rectangle)
        : UIElement{ relative, alignment, resolution },
          m_rectangle{ rectangle } { }

    bool TestElement::render() const {
        if (m_rectangle) {
            DrawRectangle(static_cast<int>(collider().x),
                          static_cast<int>(collider().y),
                          static_cast<int>(collider().width),
                          static_cast<int>(collider().height),
                          WHITE);
        } else {
            DrawRectangleLines(static_cast<int>(collider().x),
                               static_cast<int>(collider().y),
                               static_cast<int>(collider().width),
                               static_cast<int>(collider().height),
                               PURPLE);
        }


        return m_rectangle;
    }
} // namespace uil
