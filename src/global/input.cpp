//
// Purpur Tentakel
// 01.04.25
//

#include <algorithm>
#include <type_traits>
#include <uil/global/input.hpp>

namespace uil::global {
    [[nodiscard]] bool check_single_input(auto const& list, auto const func) {
        return std::ranges::any_of(list, [&](auto const key) { return std::invoke(func, key); });
    }

    [[nodiscard]] bool check_input(auto const& mouse_list,
                                   auto const mouse_func,
                                   auto const& keyboard_list,
                                   auto const keyboard_func) {
        if (check_single_input(mouse_list, mouse_func)) {
            return true;
        }
        return check_single_input(keyboard_list, keyboard_func);
    }

    void InputManager::set_accept_keys_mouse(std::vector<int> accept_keys_mouse) {
        m_accept_keys_mouse = std::move(accept_keys_mouse);
    }
    std::vector<int> InputManager::accept_keys_mouse() const {
        return m_accept_keys_mouse;
    }
    void InputManager::set_accept_keys_keyboard(std::vector<int> accept_keys_keyboard) {
        m_accept_keys_keyboard = std::move(accept_keys_keyboard);
    }
    std::vector<int> InputManager::accept_keys_keyboard() const {
        return m_accept_keys_keyboard;
    }

    bool InputManager::is_accept_input_down() const {
        return check_input(m_accept_keys_mouse, IsMouseButtonDown, m_accept_keys_keyboard, IsKeyDown);
    }
    bool InputManager::is_accept_input_up() const {
        return not is_accept_input_down();
    }
    bool InputManager::is_accept_input_pressed() const {
        return check_input(m_accept_keys_mouse, IsMouseButtonPressed, m_accept_keys_keyboard, IsKeyPressed);
    }
    bool InputManager::is_accept_input_released() const {
        return check_input(m_accept_keys_mouse, IsMouseButtonReleased, m_accept_keys_keyboard, IsKeyReleased);
    }

    void InputManager::set_reject_keys_mouse(std::vector<int> reject_keys_mouse) {
        m_reject_keys_mouse = std::move(reject_keys_mouse);
    }
    std::vector<int> InputManager::reject_keys_mouse() const {
        return m_reject_keys_mouse;
    }
    void InputManager::set_reject_keys_keyboard(std::vector<int> reject_keys_keyboard) {
        m_reject_keys_keyboard = std::move(reject_keys_keyboard);
    }
    std::vector<int> InputManager::reject_keys_keyboard() const {
        return m_reject_keys_keyboard;
    }

    bool InputManager::is_reject_input_down() const {
        return check_input(m_reject_keys_mouse, IsMouseButtonDown, m_reject_keys_keyboard, IsKeyDown);
    }
    bool InputManager::is_reject_input_up() const {
        return check_input(m_reject_keys_mouse, IsMouseButtonUp, m_reject_keys_keyboard, IsKeyUp);
    }
    bool InputManager::is_reject_input_pressed() const {
        return check_input(m_reject_keys_mouse, IsMouseButtonPressed, m_reject_keys_keyboard, IsKeyPressed);
    }
    bool InputManager::is_reject_input_released() const {
        return check_input(m_reject_keys_mouse, IsMouseButtonReleased, m_reject_keys_keyboard, IsKeyReleased);
    }
} // namespace uil::global
