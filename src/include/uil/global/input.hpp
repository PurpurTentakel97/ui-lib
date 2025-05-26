//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <raylib.h>
#include <uil/global/input_enum.hpp>
#include <utility>

namespace uil {
    enum class ModOp {
        Or,
        And,
    };

    enum class KeyOp {
        Or,
        And,
    };

    class InputManager final {
    private:
        int m_current_controller_index{ 0 };

        // #region Ray
        template<IsRayKey R>
        [[nodiscard]] bool is_ray(auto const func_keyboard,
                                  auto const func_mouse,
                                  auto const func_gamepad,
                                  R const key) const {
            if constexpr (std::is_same_v<R, KeyboardKey>) {
                return func_keyboard(key);
            }
            if constexpr (std::is_same_v<R, MouseButton>) {
                return func_mouse(key);
            }
            if constexpr (std::is_same_v<R, GamepadButton>) {
                return func_gamepad(m_current_controller_index, key);
            }
        }

        template<IsRayKey R>
        [[nodiscard]] bool is_down_ray(R const key) const {
            return is_ray(IsKeyDown, IsMouseButtonDown, IsGamepadButtonDown, key);
        }

        template<IsRayKey R>
        [[nodiscard]] bool is_up_ray(R const key) const {
            return is_ray(IsKeyUp, IsMouseButtonUp, IsGamepadButtonUp, key);
        }

        template<IsRayKey R>
        [[nodiscard]] bool is_pressed_ray(R const key) const {
            return is_ray(IsKeyPressed, IsMouseButtonPressed, IsGamepadButtonPressed, key);
        }

        template<IsRayKey R>
        [[nodiscard]] bool is_released_ray(R const key) const {
            return is_ray(IsKeyReleased, IsMouseButtonReleased, IsGamepadButtonReleased, key);
        }

        template<IsInput I>
        [[nodiscard]] auto ray_key_from_input(I const input) const {
            if constexpr (std::is_same_v<I, Keyboard> or std::is_same_v<I, KeyboardMod>) {
                return static_cast<KeyboardKey>(input);
            }
            if constexpr (std::is_same_v<I, Mouse> or std::is_same_v<I, MouseMod>) {
                return static_cast<MouseButton>(input);
            }
            if constexpr (std::is_same_v<I, Gamepad> or std::is_same_v<I, GamepadMod>) {
                return static_cast<GamepadButton>(input);
            }
        }

        // #endregion

        // #region Internal
        template<IsInput I>
        [[nodiscard]] bool is_single_down(I const input) const {
            return is_down_ray(ray_key_from_input(input));
        }

        template<IsInput I>
        [[nodiscard]] bool is_single_up(I const input) const {
            return is_up_ray(ray_key_from_input(input));
        }

        template<IsInput I>
        [[nodiscard]] bool is_single_pressed(I const input) const {
            return is_pressed_ray(ray_key_from_input(input));
        }

        template<IsInput I>
        [[nodiscard]] bool is_single_released(I const input) const {
            return is_released_ray(ray_key_from_input(input));
        }

        template<IsInput... I>
        [[nodiscard]] bool check_input(auto const& func_keys,
                                       KeyOp const type_key,
                                       ModOp const type_mod,
                                       I const... input) const {
            auto is_missing_keys      = true;
            auto is_keys              = type_key == KeyOp::And;
            auto is_missing_modifiers = true;
            auto is_modifiers         = type_mod == ModOp::And;

            auto const perform_single_check = [&]<IsInput T>(T const key) {
                if constexpr (IsButton<T>) {
                    is_missing_keys = false;
                    switch (type_key) {
                        case KeyOp::Or: is_keys = is_keys or func_keys(key);
                            break;
                        case KeyOp::And: is_keys = is_keys and func_keys(key);
                            break;
                    }
                }
                if constexpr (IsModifier<T>) {
                    is_missing_modifiers = false;
                    switch (type_mod) {
                        case ModOp::Or: is_modifiers = is_modifiers or is_single_down(key);
                            break;
                        case ModOp::And: is_modifiers = is_modifiers and is_single_down(key);
                            break;
                    }
                }
            };

            (perform_single_check(input), ...);

            if (is_missing_keys) {
                return false;
            }
            if (is_missing_modifiers) {
                return is_keys;
            }

            return is_keys and is_modifiers;
        }

        // #endregion

    public:
        // #region Constructor
        InputManager()                               = default;
        InputManager(InputManager const&)            = delete;
        InputManager(InputManager&&)                 = delete;
        InputManager& operator=(InputManager const&) = delete;
        InputManager& operator=(InputManager&&)      = delete;
        ~InputManager()                              = default;
        // #endregion

        // #region Input
        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_down(I const... input) const {
            return check_input([&](auto const key) { return is_single_down(key); }, KeyOp, ModOp, input...);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_up(I const... input) const {
            return check_input([&](auto const key) { return is_single_up(key); }, KeyOp, ModOp, input...);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_pressed(I const... input) const {
            return check_input([&](auto const key) { return is_single_pressed(key); }, KeyOp, ModOp, input...);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_released(I const... input) const {
            return check_input([&](auto const key) { return is_single_released(key); }, KeyOp, ModOp, input...);
        }

        // #endregion

        // #region GamePad
        void set_current_gamepad_index(int index);
        [[nodiscard]] int current_gamepad_index() const;
        // #endregion
    };
} // namespace uil
