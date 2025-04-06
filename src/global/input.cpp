//
// Purpur Tentakel
// 01.04.25
//

#include <algorithm>
#include <functional>
#include <uil/global/input.hpp>

namespace uil::global {
    void InputManager::reset() {
        m_one_time_accept_input_pressed  = false;
        m_one_time_accept_input_released = false;
        m_one_time_reject_input_pressed  = false;
        m_one_time_reject_input_released = false;
    }

    void InputManager::set_use_one_time_input(bool const use_one_time_input) {
        m_use_one_time_input = use_one_time_input;
    }
    bool InputManager::use_one_time_input() const {
        return m_use_one_time_input;
    }

    [[nodiscard]] bool check_predefined_single_input(auto const& list, auto const func) {
        return std::ranges::any_of(list, [&](auto const key) { return std::invoke(func, key); });
    }

    [[nodiscard]] bool check_predefined_input(auto const& mouse_list,
                                              auto const mouse_func,
                                              auto const& keyboard_list,
                                              auto const keyboard_func) {
        if (check_predefined_single_input(mouse_list, mouse_func)) {
            return true;
        }
        return check_predefined_single_input(keyboard_list, keyboard_func);
    }

    void InputManager::set_accept_keys_mouse(std::vector<MouseButton> accept_keys_mouse) {
        m_accept_keys_mouse = std::move(accept_keys_mouse);
    }
    std::vector<MouseButton> InputManager::accept_keys_mouse() const {
        return m_accept_keys_mouse;
    }
    void InputManager::set_accept_keys_keyboard(std::vector<KeyboardKey> accept_keys_keyboard) {
        m_accept_keys_keyboard = std::move(accept_keys_keyboard);
    }
    std::vector<KeyboardKey> InputManager::accept_keys_keyboard() const {
        return m_accept_keys_keyboard;
    }

    bool InputManager::is_accept_input_down() const {
        return check_predefined_input(m_accept_keys_mouse, IsMouseButtonDown, m_accept_keys_keyboard, IsKeyDown);
    }
    bool InputManager::is_accept_input_up() const {
        return not is_accept_input_down();
    }
    bool InputManager::is_accept_input_pressed() {
        if (m_use_one_time_input && m_one_time_accept_input_pressed) {
            return false;
        }

        auto const result = is_accept_input_pressed_unchecked();

        if (m_use_one_time_input && result) {
            m_one_time_accept_input_pressed = true;
        }

        return result;
    }
    bool InputManager::is_accept_input_pressed_unchecked() const {
        return check_predefined_input(m_accept_keys_mouse, IsMouseButtonPressed, m_accept_keys_keyboard, IsKeyPressed);
    }
    bool InputManager::is_accept_input_released() {
        if (m_use_one_time_input && m_one_time_accept_input_pressed) {
            return false;
        }

        auto const result = is_accept_input_released_unchecked();

        if (m_use_one_time_input && result) {
            m_one_time_accept_input_pressed = true;
        }

        return result;
    }
    bool InputManager::is_accept_input_released_unchecked() const {
        return check_predefined_input(
                m_accept_keys_mouse, IsMouseButtonReleased, m_accept_keys_keyboard, IsKeyReleased);
    }

    void InputManager::set_reject_keys_mouse(std::vector<MouseButton> reject_keys_mouse) {
        m_reject_keys_mouse = std::move(reject_keys_mouse);
    }
    std::vector<MouseButton> InputManager::reject_keys_mouse() const {
        return m_reject_keys_mouse;
    }
    void InputManager::set_reject_keys_keyboard(std::vector<KeyboardKey> reject_keys_keyboard) {
        m_reject_keys_keyboard = std::move(reject_keys_keyboard);
    }
    std::vector<KeyboardKey> InputManager::reject_keys_keyboard() const {
        return m_reject_keys_keyboard;
    }

    bool InputManager::is_reject_input_down() const {
        return check_predefined_input(m_reject_keys_mouse, IsMouseButtonDown, m_reject_keys_keyboard, IsKeyDown);
    }
    bool InputManager::is_reject_input_up() const {
        return check_predefined_input(m_reject_keys_mouse, IsMouseButtonUp, m_reject_keys_keyboard, IsKeyUp);
    }
    bool InputManager::is_reject_input_pressed() {
        if (m_use_one_time_input && m_one_time_reject_input_pressed) {
            return false;
        }

        auto const result = is_reject_input_pressed_unchecked();

        if (m_use_one_time_input && result) {
            m_one_time_reject_input_pressed = true;
        }

        return result;
    }
    bool InputManager::is_reject_input_pressed_unchecked() const {
        return check_predefined_input(m_reject_keys_mouse, IsMouseButtonPressed, m_reject_keys_keyboard, IsKeyPressed);
        ;
    }
    bool InputManager::is_reject_input_released() {
        if (m_use_one_time_input && m_one_time_reject_input_released) {
            return false;
        }

        auto const result = is_reject_input_released_unchecked();

        if (m_use_one_time_input && result) {
            m_one_time_reject_input_released = true;
        }

        return result;
    }
    bool InputManager::is_reject_input_released_unchecked() const {
        return check_predefined_input(
                m_reject_keys_mouse, IsMouseButtonReleased, m_reject_keys_keyboard, IsKeyReleased);
    }

    [[nodiscard]] bool check_key_modified(auto const key, std::span<KeyboardKey const> modifier, auto const func) {
        if (modifier.empty()) {
            return std::invoke(func, key);
        }

        auto const modifier_pressed = std::ranges::any_of(modifier, [](auto const k) { return IsKeyDown(k); });
        if (not modifier_pressed) {
            return false;
        }

        return std::invoke(func, key);
    }

    bool InputManager::is_key_down(KeyboardKey const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsKeyDown);
    }
    bool InputManager::is_key_up(KeyboardKey const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsKeyUp);
    }
    bool InputManager::is_key_pressed(KeyboardKey const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsKeyPressed);
    }
    bool InputManager::is_key_released(KeyboardKey const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsKeyReleased);
    }

    bool InputManager::is_mouse_down(MouseButton const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsMouseButtonDown);
    }
    bool InputManager::is_mouse_up(MouseButton const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsMouseButtonUp);
    }
    bool InputManager::is_mouse_pressed(MouseButton const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsMouseButtonPressed);
    }
    bool InputManager::is_mouse_released(MouseButton const key, std::span<KeyboardKey const> const modifier) {
        return check_key_modified(key, modifier, IsMouseButtonReleased);
    }
} // namespace uil::global
