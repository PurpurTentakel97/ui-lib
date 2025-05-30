//
// Purpur Tentakel
// 26.05.25
//

#include <tuple>
#include <uil/focus_element.hpp>
#include <uil/global/app_context.hpp>
#include <uil/global/focus.hpp>

namespace uil {
    static FocusManager::FocusBindingConfig default_config{
        { FocusAction::Next,
         {
                  {
                          Keyboard::KEY_TAB,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
                  },
          } },

        { FocusAction::Previous,
         {
                  {
                          Keyboard::KEY_TAB,
                          KeyboardMod::KEY_LEFT_SHIFT,
                          KeyboardMod::KEY_RIGHT_SHIFT,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_LEFT_TRIGGER_1,
                  },
          } },

        { FocusAction::Left,
         {
                  {
                          Keyboard::KEY_LEFT,
                          Keyboard::KEY_A,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_LEFT_FACE_LEFT,
                  },
          } },

        { FocusAction::Right,
         {
                  {
                          Keyboard::KEY_RIGHT,
                          Keyboard::KEY_D,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
                  },
          } },

        { FocusAction::Up,
         {
                  {
                          Keyboard::KEY_UP,
                          Keyboard::KEY_W,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_LEFT_FACE_UP,
                  },
          } },
        { FocusAction::Down,
         {
                  {
                          Keyboard::KEY_DOWN,
                          Keyboard::KEY_S,
                  },
                  {
                          Gamepad::GAMEPAD_BUTTON_LEFT_FACE_DOWN,
                  },
          } },
    };
}; // namespace uil


namespace uil {
    tl::optional<std::shared_ptr<FocusElement>> FocusManager::current() {
        if (m_current.empty()) {
            return tl::nullopt;
        }
        return m_current.back();
    }
    void FocusManager::unfocus_current() {
        if (auto const current_element = current()) {
            current_element.value()->unfocus();
        }
    }
    void FocusManager::focus_current() {
        if (auto const current_element = current()) {
            current_element.value()->focus();
        }
    }
    void FocusManager::set_new_focus(std::shared_ptr<FocusElement> const& next) {
        unfocus_current();
        set_current(next);
        focus_current();
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

    void FocusManager::push_back(std::weak_ptr<FocusElement> element) {
        if (element.expired()) {
            cpt::log::error("Provided Focus element was expired");
            return;
        }
        unfocus_current();
        m_current.push_back(element.lock());
        focus_current();
        focus_current();
    }
    void FocusManager::pop_back() {
        unfocus_current();
        if (m_current.empty()) {
            return;
        }
        m_current.pop_back();
        focus_current();
    }
    void FocusManager::set_current(std::weak_ptr<FocusElement> element) {
        if (element.expired()) {
            cpt::log::error("Provided Focus element was expired");
            return;
        }
        unfocus_current();
        if (m_current.empty()) {
            m_current.push_back(element.lock());
        } else {
            m_current.back() = element.lock();
        }
        focus_current();
    }
    void FocusManager::clear() {
        unfocus_current();
        m_current.clear();
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
            cpt::log::error("No binding for requested action is present. Enum value: {}", static_cast<int>(action));
            return {};
        }

        return m_bindings.at(action);
    }

    void FocusManager::update() {
        if (m_is_locked) {
            return;
        }

        if (m_current.empty()) {
            return;
        }

        auto const& input = AppContext::instance().input();

        auto check_input = [&](auto const& bindings) {
            if (input.is_pressed(bindings.layer_1)) {
                return true;
            }
            if (input.is_pressed(bindings.layer_2)) {
                return true;
            }
            return input.is_pressed(bindings.layer_3);
        };


        auto const update_focus = [&](auto const& element) {
            if (element.expired()) {
                return;
            }
            set_new_focus(element.lock());
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
