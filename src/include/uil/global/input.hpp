//
// Purpur Tentakel
// 30.03.25
//

#pragma once
#include <raylib.h>
#include <vector>

namespace uil::global {
    class InputManager final {
    private:
        std::vector<int> m_accept_keys_mouse{ MOUSE_BUTTON_LEFT };
        std::vector<int> m_accept_keys_keyboard{ KEY_SPACE, KEY_ENTER, KEY_KP_ENTER };
        std::vector<int> m_reject_keys_mouse{};
        std::vector<int> m_reject_keys_keyboard{ KEY_ESCAPE, KEY_BACK };

    public:
        void set_accept_keys_mouse(std::vector<int> accept_keys_mouse);
        [[nodiscard]] std::vector<int> accept_keys_mouse() const;
        void set_accept_keys_keyboard(std::vector<int> accept_keys_keyboard);
        [[nodiscard]] std::vector<int> accept_keys_keyboard() const;

        [[nodiscard]] bool is_accept_input_down() const;
        [[nodiscard]] bool is_accept_input_up() const;
        [[nodiscard]] bool is_accept_input_pressed() const;
        [[nodiscard]] bool is_accept_input_released() const;

        void set_reject_keys_mouse(std::vector<int> reject_keys_mouse);
        [[nodiscard]] std::vector<int> reject_keys_mouse() const;
        void set_reject_keys_keyboard(std::vector<int> reject_keys_keyboard);
        [[nodiscard]] std::vector<int> reject_keys_keyboard() const;

        [[nodiscard]] bool is_reject_input_down() const;
        [[nodiscard]] bool is_reject_input_up() const;
        [[nodiscard]] bool is_reject_input_pressed() const;
        [[nodiscard]] bool is_reject_input_released() const;
    };
} // namespace uil::global
