//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <tl/optional.hpp>
#include <uil/global/input.hpp>
#include <memory>

namespace uil {
    class FocusElement;
} // namespace uil

namespace uil {
    enum class FocusAction {
        Next,
        Previous,
        Up,
        Down,
        Left,
        Right,
    };

    struct FocusInputBindings final {
        InputManager::VectorInput layer_1{};
        InputManager::VectorInput layer_2{};
        InputManager::VectorInput layer_3{};
    };


    class FocusManager final {
    public:
        using FocusBindingConfig = std::unordered_map<FocusAction, FocusInputBindings>;

    private:
        bool m_is_locked = false;
        std::vector<std::shared_ptr<FocusElement>> m_current{};
        FocusBindingConfig m_bindings;

        [[nodiscard]] tl::optional<std::shared_ptr<FocusElement>> current();
        void unfocus_current();
        void focus_current();
        void set_new_focus(std::shared_ptr<FocusElement> const& next);

    public:
        FocusManager();

        void lock();
        void unlock();
        [[nodiscard]] bool is_locked() const;

        void push_back(std::weak_ptr<FocusElement> element);
        void pop_back();
        void set_current(std::weak_ptr<FocusElement> element);
        void clear();

        void set_config(FocusBindingConfig config);
        [[nodiscard]] FocusBindingConfig config() const;
        void set_single_config(FocusAction action, FocusInputBindings const& bindings);
        [[nodiscard]] FocusInputBindings single_config(FocusAction action) const;

        void update();
    };
} // namespace uil
