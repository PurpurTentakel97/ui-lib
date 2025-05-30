//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <raylib.h>
#include <uil/global/input_enum.hpp>
#include <utility>
#include <variant>
#include <vector>

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
    public:
        template<IsInput... I>
        using VariantType  = std::variant<I...>;
        using VariantInput = VariantType<Keyboard, KeyboardMod, Mouse, MouseMod, Gamepad, GamepadMod>;
        using VectorInput  = std::vector<VariantInput>;

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

        template<IsInput I>
        void perform_single_check(auto const& func_keys,
                                  KeyOp const type_key,
                                  ModOp const type_mod,
                                  I const input,
                                  bool& is_missing_keys,
                                  bool& is_keys,
                                  bool& is_missing_modifiers,
                                  bool& is_modifiers) const {
            if constexpr (IsButton<I>) {
                is_missing_keys = false;
                switch (type_key) {
                    case KeyOp::Or: is_keys = is_keys or func_keys(input); break;
                    case KeyOp::And: is_keys = is_keys and func_keys(input); break;
                }
            }
            if constexpr (IsModifier<I>) {
                is_missing_modifiers = false;
                switch (type_mod) {
                    case ModOp::Or: is_modifiers = is_modifiers or is_single_down(input); break;
                    case ModOp::And: is_modifiers = is_modifiers and is_single_down(input); break;
                }
            }
        }

        [[nodiscard]] bool check_vec_input(auto const& func_keys,
                                           KeyOp type_key,
                                           ModOp type_mod,
                                           VectorInput const& input) const {
            auto is_missing_keys      = true;
            auto is_keys              = type_key == KeyOp::And;
            auto is_missing_modifiers = true;
            auto is_modifiers         = type_mod == ModOp::And;


            for (auto const& key : input) {
                std::visit(
                        [&](auto const k) {
                            perform_single_check(func_keys,
                                                 type_key,
                                                 type_mod,
                                                 k,
                                                 is_missing_keys,
                                                 is_keys,
                                                 is_missing_modifiers,
                                                 is_modifiers);
                        },
                        key);
            }

            if (is_missing_keys) {
                return false;
            }
            if (is_missing_modifiers) {
                return is_keys;
            }

            return is_keys and is_modifiers;
        }


        template<IsInput... I>
        [[nodiscard]] bool check_variadic_input(auto const& func_keys,
                                                KeyOp const type_key,
                                                ModOp const type_mod,
                                                I const... input) const {
            auto is_missing_keys      = true;
            auto is_keys              = type_key == KeyOp::And;
            auto is_missing_modifiers = true;
            auto is_modifiers         = type_mod == ModOp::And;

            (perform_single_check(func_keys,
                                  type_key,
                                  type_mod,
                                  input,
                                  is_missing_keys,
                                  is_keys,
                                  is_missing_modifiers,
                                  is_modifiers),
             ...);

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
            return check_variadic_input([&](auto const key) { return is_single_down(key); }, KeyOp, ModOp, input...);
        }
        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or>
        [[nodiscard]] bool is_down(VectorInput const& input) const {
            return check_vec_input([&](auto const key) { return is_single_down(key); }, KeyOp, ModOp, input);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_up(I const... input) const {
            return check_variadic_input([&](auto const key) { return is_single_up(key); }, KeyOp, ModOp, input...);
        }
        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or>
        [[nodiscard]] bool is_up(VectorInput const& input) const {
            return check_vec_input([&](auto const key) { return is_single_up(key); }, KeyOp, ModOp, input);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_pressed(I const... input) const {
            return check_variadic_input([&](auto const key) { return is_single_pressed(key); }, KeyOp, ModOp, input...);
        }
        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or>
        [[nodiscard]] bool is_pressed(VectorInput const& input) const {
            return check_vec_input([&](auto const key) { return is_single_pressed(key); }, KeyOp, ModOp, input);
        }

        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or, IsInput... I>
        [[nodiscard]] bool is_released(I const... input) const {
            return check_variadic_input(
                    [&](auto const key) { return is_single_released(key); }, KeyOp, ModOp, input...);
        }
        template<KeyOp KeyOp = KeyOp::Or, ModOp ModOp = ModOp::Or>
        [[nodiscard]] bool is_released(VectorInput const& input) const {
            return check_vec_input([&](auto const key) { return is_single_released(key); }, KeyOp, ModOp, input);
        }

        // #endregion

        // #region GamePad
        void set_current_gamepad_index(int index);
        [[nodiscard]] int current_gamepad_index() const;
        // #endregion
    };
} // namespace uil
