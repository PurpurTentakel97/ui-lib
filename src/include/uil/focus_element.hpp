//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <memory>
#include <cpt/callback.hpp>

namespace uil {
    class FocusElement;
}

namespace uil {
    struct FocusConfig final {
        std::weak_ptr<FocusElement> previous;
        std::weak_ptr<FocusElement> next;
        std::weak_ptr<FocusElement> left;
        std::weak_ptr<FocusElement> right;
        std::weak_ptr<FocusElement> up;
        std::weak_ptr<FocusElement> down;
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
        ~FocusElement();

        cpt::Callback<FocusElement&> on_focus{};
        cpt::Callback<FocusElement&> on_unfocus{};

        void set_focus_config(FocusConfig const& config);
        [[nodiscard]] FocusConfig const& focus_config() const;

        [[nodiscard]] bool is_focused() const;
    };
} // namespace uil
