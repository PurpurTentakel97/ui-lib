//
// Purpur Tentakel
// 26.05.25
//

#include <uil/focus_element.hpp>
#include <uil/global/app_context.hpp>

namespace uil {
    void FocusElement::focus() {
        m_is_focused = true;
        on_focus.invoke(*this);
    }
    void FocusElement::unfocus() {
        m_is_focused = false;
        on_unfocus.invoke(*this);
    }

    FocusElement::~FocusElement() {
        if (m_is_focused) {
            AppContext::instance().focus().pop_back();
        }
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
