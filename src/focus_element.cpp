//
// Purpur Tentakel
// 26.05.25
//

#include <uil/focus_element.hpp>

namespace uil {
    void FocusElement::focus() {
        m_is_focused = true;
    }
    void FocusElement::unfocus() {
        m_is_focused = false;
    }

    void FocusElement::set_focus_config(FocusConfig const& config) {
        m_focus_config = config;
    }
    FocusConfig const& FocusElement::focus_config() const {
        return m_focus_config;
    }

    bool FocusElement::is_focused() const {
        return m_is_focused;
    }
} // namespace uil
