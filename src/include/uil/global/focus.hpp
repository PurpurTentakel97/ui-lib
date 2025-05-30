//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <tl/optional.hpp>
#include <uil/global/input_enum.hpp>

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
        tl::optional<Keyboard> key_1;
        tl::optional<Keyboard> key_2;
        tl::optional<KeyboardMod> key_mod_1;
        tl::optional<KeyboardMod> key_mod_2;
        tl::optional<Gamepad> pad_1;
        tl::optional<Gamepad> pad_2;
    };


    class FocusManager final {
    public:
        using FocusBindingConfig = std::unordered_map<FocusAction, FocusInputBindings>;

    private:
        bool m_is_locked = false;
        std::vector<FocusElement*> m_current{};
        FocusBindingConfig m_bindings;
        [[nodiscard]] tl::optional<FocusElement*> current();

    public:
        FocusManager();

        void lock();
        void unlock();
        [[nodiscard]] bool is_locked() const;


        void set_config(FocusBindingConfig config);
        [[nodiscard]] FocusBindingConfig config() const;
        void set_single_config(FocusAction action, FocusInputBindings const& bindings);
        [[nodiscard]] FocusInputBindings single_config(FocusAction action) const;

        void update();
    };
} // namespace uil
