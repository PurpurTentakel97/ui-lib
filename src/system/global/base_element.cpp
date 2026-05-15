//
// Purpur Tentakel
// 07.08.24
//

#include <../include/system/global/base_element.hpp>

namespace uil::sys {
    bool BaseElement::active() const {
        return m_active;
    }

    void BaseElement::set_active(bool const active) {
        m_active = active;
    }
} // namespace uil
