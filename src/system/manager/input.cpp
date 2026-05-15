//
// Purpur Tentakel
// 31.05.25
//

#include <../include/system/manager/input.hpp>

namespace uil {
    static const inline InputManager::BindingsConfig s_default_bindings{
        { InputManager::Pattern::Accept,
         { {
                    Keyboard::KEY_ENTER,
                    Keyboard::KEY_KP_ENTER,
            },
            {
                    Gamepad::GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
            } } },
        { InputManager::Pattern::Deny,
         { {
                    Keyboard::KEY_ESCAPE,
            },
            {
                    Gamepad::GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
            } } }
    };
}

namespace uil {

    InputManager::InputManager() : m_bindings{ s_default_bindings } { }
    void InputManager::set_bindings(BindingsConfig const& bindings) {
        m_bindings = bindings;
    }
    InputManager::BindingsConfig const& InputManager::bindings() const {
        return m_bindings;
    }

    void InputManager::set_specific_binding(Pattern const pattern, Bindings const& bindings) {
        m_bindings[pattern] = bindings;
    }
    tl::expected<InputManager::Bindings, InputManager::Result> InputManager::specific_binding(
            Pattern const pattern) const {
        if (not m_bindings.contains(pattern)) {
            cpt::log::r_error("[[InputManager]] No bindings for pattern: '{}'", static_cast<int>(pattern));
            return tl::unexpected{ Result::MissingBindings };
        }

        return m_bindings.at(pattern);
    }
} // namespace uil
