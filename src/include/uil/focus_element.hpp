//
// Purpur Tentakel
// 26.05.25
//

#pragma once
#include <uil/global/focus.hpp>

namespace uil {
    struct FocusConfig final {
        FocusElement* previous = nullptr;
        FocusElement* next     = nullptr;
        FocusElement* left     = nullptr;
        FocusElement* right    = nullptr;
        FocusElement* up       = nullptr;
        FocusElement* down     = nullptr;
    };

    class FocusElement {
    public:
        friend class FocusManager;
    private:
        bool m_is_focused = false;
        FocusConfig m_focus_config{};

        void focus();
        void unfocus();

    public:
        void set_focus_config(FocusConfig const& config);
        [[nodiscard]] FocusConfig const& focus_config() const;

        [[nodiscard]] bool is_focused() const;
    };
}
