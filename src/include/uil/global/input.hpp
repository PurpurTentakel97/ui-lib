//
// Purpur Tentakel
// 30.03.25
//

#pragma once
#include <array>
#include <raylib.h>
#include <span>
#include <vector>

namespace uil::global {
    class InputManager final {
    public:
        friend class AppContext;

        static constexpr std::array<KeyboardKey, 2> s_shift_modifier{ KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT };
        static constexpr std::array<KeyboardKey, 2> s_ctrl_modifier{ KEY_LEFT_CONTROL, KEY_RIGHT_CONTROL };
        static constexpr std::array<KeyboardKey, 2> s_alt_modifier{ KEY_LEFT_ALT, KEY_RIGHT_ALT };
        static constexpr std::array<KeyboardKey, 2> s_up_direction_modifier{ KEY_W, KEY_UP };
        static constexpr std::array<KeyboardKey, 2> s_right_direction_modifier{ KEY_D, KEY_RIGHT };
        static constexpr std::array<KeyboardKey, 2> s_down_direction_modifier{ KEY_S, KEY_DOWN };
        static constexpr std::array<KeyboardKey, 2> s_left_direction_modifier{ KEY_A, KEY_LEFT };

    private:
        std::vector<MouseButton> m_accept_keys_mouse{ MOUSE_BUTTON_LEFT };
        std::vector<KeyboardKey> m_accept_keys_keyboard{ KEY_SPACE, KEY_ENTER, KEY_KP_ENTER };
        std::vector<MouseButton> m_reject_keys_mouse{};
        std::vector<KeyboardKey> m_reject_keys_keyboard{ KEY_ESCAPE, KEY_BACK };

        bool m_use_one_time_input{ false };
        bool m_one_time_accept_input_pressed{ false };
        bool m_one_time_accept_input_released{ false };
        bool m_one_time_reject_input_pressed{ false };
        bool m_one_time_reject_input_released{ false };

        void reset();

    public:
        void set_use_one_time_input(bool use_one_time_input);
        [[nodiscard]] bool use_one_time_input() const;

        void set_accept_keys_mouse(std::vector<MouseButton> accept_keys_mouse);
        [[nodiscard]] std::vector<MouseButton> accept_keys_mouse() const;
        void set_accept_keys_keyboard(std::vector<KeyboardKey> accept_keys_keyboard);
        [[nodiscard]] std::vector<KeyboardKey> accept_keys_keyboard() const;

        [[nodiscard]] bool is_accept_input_down() const;
        [[nodiscard]] bool is_accept_input_up() const;
        [[nodiscard]] bool is_accept_input_pressed();
        [[nodiscard]] bool is_accept_input_pressed_unchecked() const;
        [[nodiscard]] bool is_accept_input_released();
        [[nodiscard]] bool is_accept_input_released_unchecked() const;

        void set_reject_keys_mouse(std::vector<MouseButton> reject_keys_mouse);
        [[nodiscard]] std::vector<MouseButton> reject_keys_mouse() const;
        void set_reject_keys_keyboard(std::vector<KeyboardKey> reject_keys_keyboard);
        [[nodiscard]] std::vector<KeyboardKey> reject_keys_keyboard() const;

        [[nodiscard]] bool is_reject_input_down() const;
        [[nodiscard]] bool is_reject_input_up() const;
        [[nodiscard]] bool is_reject_input_pressed();
        [[nodiscard]] bool is_reject_input_pressed_unchecked() const;
        [[nodiscard]] bool is_reject_input_released();
        [[nodiscard]] bool is_reject_input_released_unchecked() const;

        [[nodiscard]] static bool is_key_down(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_key_up(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_key_pressed(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_key_released(KeyboardKey key, std::span<KeyboardKey const> modifier = {});

        [[nodiscard]] static bool is_mouse_down(MouseButton key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_mouse_up(MouseButton key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_mouse_pressed(MouseButton key, std::span<KeyboardKey const> modifier = {});
        [[nodiscard]] static bool is_mouse_released(MouseButton key, std::span<KeyboardKey const> modifier = {});
    };
} // namespace uil::global
