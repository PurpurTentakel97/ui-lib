//
// Purpur Tentakel
// 26.05.25
//

#include <tuple>
#include <uil/focus_element.hpp>
#include <uil/global/app_context.hpp>
#include <uil/global/focus.hpp>

namespace uil {
    // clang-format off
    static FocusManager::FocusBindingConfig default_config{
        { FocusAction::Next, {
            Keyboard::KEY_TAB,
            {},
            {},
            {},
             Gamepad::GAMEPAD_BUTTON_RIGHT_TRIGGER_1 ,
            {},
        }},
        { FocusAction::Previous, {
            Keyboard::KEY_TAB,
            {},
            KeyboardMod::KEY_LEFT_SHIFT,
            KeyboardMod::KEY_RIGHT_SHIFT,
            Gamepad::GAMEPAD_BUTTON_LEFT_TRIGGER_1,
            {},
        }},
        { FocusAction::Left, {
            Keyboard::KEY_LEFT,
            Keyboard::KEY_A,
            {},
            {},
            Gamepad::GAMEPAD_BUTTON_LEFT_FACE_LEFT,
            {},
        }},
        { FocusAction::Right, {
            Keyboard::KEY_RIGHT,
            Keyboard::KEY_D,
            {},
            {},
            Gamepad::GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
            {},
        }},
        { FocusAction::Up, {
            Keyboard::KEY_UP,
            Keyboard::KEY_W,
            {},
            {},
            Gamepad::GAMEPAD_BUTTON_LEFT_FACE_UP,
            {},
        }},
        { FocusAction::Down, {
            Keyboard::KEY_DOWN,
            Keyboard::KEY_S,
            {},
            {},
            Gamepad::GAMEPAD_BUTTON_LEFT_FACE_DOWN,
            {},
        }},
    };
    // clang-format on
}; // namespace uil


namespace uil {
    tl::optional<FocusElement*> FocusManager::current() {
        if (m_current.empty()) {
            return tl::nullopt;
        }
        return m_current.back();
    }

    FocusManager::FocusManager() : m_bindings{ default_config } { }

    void FocusManager::lock() {
        m_is_locked = true;
    }
    void FocusManager::unlock() {
        m_is_locked = false;
    }
    bool FocusManager::is_locked() const {
        return m_is_locked;
    }


    void FocusManager::set_config(FocusBindingConfig config) {
        m_bindings = std::move(config);
    }

    FocusManager::FocusBindingConfig FocusManager::config() const {
        return m_bindings;
    }

    void FocusManager::set_single_config(FocusAction const action, FocusInputBindings const& bindings) {
        m_bindings[action] = bindings;
    }

    FocusInputBindings FocusManager::single_config(FocusAction const action) const {
        if (not m_bindings.contains(action)) {
            cpt::log::error("no binding for requested action presend. Enum value: {}", static_cast<int>(action));
            return {};
        }

        return m_bindings.at(action);
    }

    template<typename... I>
    static bool is_pressed_wrapper(I... inputs) {
        return AppContext::instance().input().is_pressed(inputs...);
    }

    void FocusManager::update() {
        if (m_is_locked) {
            return;
        }

        if (m_current.empty()) {
            return;
        }

        // auto const& input = AppContext::instance().input();

        auto check_input = [&](auto ) { return false; };


        auto const update_focus = [&](auto* element) {
            if (!element) {
                return;
            }
            // set_new_focus(element);
        };

        // Check previous first because on PC it is likely the same key as the next key but with modifier. It would not trigger then.
        if (m_bindings.contains(FocusAction::Previous) && check_input(m_bindings[FocusAction::Previous])) {
            update_focus(m_current.back()->focus_config().previous);
            return;
        }
        if (m_bindings.contains(FocusAction::Next) && check_input(m_bindings[FocusAction::Next])) {
            update_focus(m_current.back()->focus_config().next);
            return;
        }
        if (m_bindings.contains(FocusAction::Left) && check_input(m_bindings[FocusAction::Left])) {
            update_focus(m_current.back()->focus_config().left);
            return;
        }
        if (m_bindings.contains(FocusAction::Right) && check_input(m_bindings[FocusAction::Right])) {
            update_focus(m_current.back()->focus_config().right);
            return;
        }
        if (m_bindings.contains(FocusAction::Up) && check_input(m_bindings[FocusAction::Up])) {
            update_focus(m_current.back()->focus_config().up);
            return;
        }
        if (m_bindings.contains(FocusAction::Down) && check_input(m_bindings[FocusAction::Down])) {
            update_focus(m_current.back()->focus_config().down);
            return;
        }
    }
} // namespace uil
