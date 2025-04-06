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
    /**
     * This class handles all input Requests.
     * Call this from the AppContext.
     * It also provides standard modifier.
     */
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
        /**
         * the one-time-input prevents multiple input in one frame for one time actions like pressed or released.
         *
         * @param use_one_time_input sets weather the one time input on one frame actions is used or not.
         */
        void set_use_one_time_input(bool use_one_time_input);
        /**
         *
         * @return weather the one time input on one frame actions is set.
         */
        [[nodiscard]] bool use_one_time_input() const;

        /**
         *
         * @param accept_keys_mouse sets the accept-keys for mouse actions.
         */
        void set_accept_keys_mouse(std::vector<MouseButton> accept_keys_mouse);
        /**
         *
         * @return returns the currently set accept-keys for mouse actions.
         */
        [[nodiscard]] std::vector<MouseButton> accept_keys_mouse() const;
        /**
         *
         * @param accept_keys_keyboard sets the accept-keys for keyboard actions.
         */
        void set_accept_keys_keyboard(std::vector<KeyboardKey> accept_keys_keyboard);
        /**
         *
         * @return returns the currently set accept-keys for keyboard actions.
         */
        [[nodiscard]] std::vector<KeyboardKey> accept_keys_keyboard() const;

        /**
         * note: does not use the one-time-input.
         *
         * @return true if any accept input is down.
         */
        [[nodiscard]] bool is_accept_input_down() const;
        /**
         * note: does not use the one-time-input.
         *
         * @return true if all accept inputs are up.
         */
        [[nodiscard]] bool is_accept_input_up() const;
        /**
         * note: uses the one-time-input if configured.
         *
         * @return true if any accept input is pressed.
         */
        [[nodiscard]] bool is_accept_input_pressed();
        /**
         * note: does not use the one-time-input event if it is configured.
         *
         * @return true if any accept input is pressed.
         */
        [[nodiscard]] bool is_accept_input_pressed_unchecked() const;
        /**
         * note: uses the one-time-input if configured.
         *
         * @return true if any accept input is released.
         */
        [[nodiscard]] bool is_accept_input_released();
        /**
         * note: does not use the one-time-input event if it is configured.
         *
         * @return true if any accept input is released.
         */
        [[nodiscard]] bool is_accept_input_released_unchecked() const;

        /**
         *
         * @param reject_keys_mouse sets the reject-keys for mouse actions.
         */
        void set_reject_keys_mouse(std::vector<MouseButton> reject_keys_mouse);
        /**
         *
         * @return returns the currently set reject-keys for mouse actions.
         */
        [[nodiscard]] std::vector<MouseButton> reject_keys_mouse() const;
        /**
         *
         * @param reject_keys_keyboard sets the reject-keys for keyboard actions.
         */
        void set_reject_keys_keyboard(std::vector<KeyboardKey> reject_keys_keyboard);
        /**
         *
         * @return returns the currently set reject-keys for keyboard actions.
         */
        [[nodiscard]] std::vector<KeyboardKey> reject_keys_keyboard() const;

        /**
         * note: does not use the one-time-input.
         *
         * @return true if any reject input is down.
         */
        [[nodiscard]] bool is_reject_input_down() const;
        /**
         * note: does not use the one-time-input.
         *
         * @return true if all reject input are up.
         */
        [[nodiscard]] bool is_reject_input_up() const;
        /**
         * note: uses the one-time-input if configured.
         *
         * @return true if any reject input is pressed.
         */
        [[nodiscard]] bool is_reject_input_pressed();
        /**
         * note: does not use the one-time-input even if configured.
         *
         * @return true if any reject input is pressed.
         */
        [[nodiscard]] bool is_reject_input_pressed_unchecked() const;
        /**
         * note: uses the one-time-input if configured.
         *
         * @return true if any reject input is released.
         */
        [[nodiscard]] bool is_reject_input_released();
        /**
         * note: does not use the one-time-input even if configured.
         *
         * @return true if any reject input is released.
         */
        [[nodiscard]] bool is_reject_input_released_unchecked() const;

        /**
         *
         * @param key Keyboard key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key is down.
         */
        [[nodiscard]] static bool is_key_down(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Keyboard key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key is up.
         */
        [[nodiscard]] static bool is_key_up(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Keyboard key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was pressed.
         */
        [[nodiscard]] static bool is_key_pressed(KeyboardKey key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Keyboard key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was released.
         */
        [[nodiscard]] static bool is_key_released(KeyboardKey key, std::span<KeyboardKey const> modifier = {});

        /**
         *
         * @param key Mouse key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was down.
         */
        [[nodiscard]] static bool is_mouse_down(MouseButton key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Mouse key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was up.
         */
        [[nodiscard]] static bool is_mouse_up(MouseButton key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Mouse key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was pressed.
         */
        [[nodiscard]] static bool is_mouse_pressed(MouseButton key, std::span<KeyboardKey const> modifier = {});
        /**
         *
         * @param key Mouse key, that going to be checked.
         * @param modifier list of keyboard modifiers that needs to be down.
         * @return true if at least one modifier is down and the key was released.
         */
        [[nodiscard]] static bool is_mouse_released(MouseButton key, std::span<KeyboardKey const> modifier = {});
    };
} // namespace uil::global
