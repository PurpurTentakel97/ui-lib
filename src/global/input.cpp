//
// Purpur Tentakel
// 15.04.25
//

#include <uil/global/input.hpp>

namespace uil {
    void InputManager::set_current_gamepad_index(int const index) {
        m_current_controller_index = index;
    }
    int InputManager::current_gamepad_index() const {
        return m_current_controller_index;
    }
} // namespace uil
