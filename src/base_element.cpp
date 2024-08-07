//
// Purpur Tentakel
// 07.08.24
//

#include <uil/base_element.hpp>

namespace uil {
    bool BaseElement::active() const {
        return m_active;
    }

    void BaseElement::set_active(bool const active) {
        m_active = active;
    }
} // namespace uil
