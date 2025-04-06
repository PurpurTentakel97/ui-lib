//
// Purpur Tentakel
// 30.03.25
//

#pragma once
#include <algorithm>
#include <array>
#include <cpt/types.hpp>
#include <ranges>
#include <raylib.h>
#include <unordered_map>
#include <variant>
#include <vector>

namespace uil::global {
    template<typename T>
    concept IsKey
            = std::is_same_v<T, MouseButton> or std::is_same_v<T, KeyboardKey> or std::is_same_v<T, GamepadButton>;

    class InputManager final {
    private:
        using Key    = std::variant<MouseButton, KeyboardKey, GamepadButton>;
        using KeyMap = std::unordered_map<cpt::usize, std::vector<Key>>;
        KeyMap m_key_collections{};
        cpt::usize m_id_counter{ 1 };

        [[nodiscard]] cpt::usize next_id();

        // ---------------------------------------------------

        template<IsKey T>
        [[nodiscard]] static bool is_action(T key, auto mouse_function, auto keyboard_function, auto gamepad_function) {
            if constexpr (std::is_same_v<T, MouseButton>) {
                return mouse_function(key);
            }
            if constexpr (std::is_same_v<T, KeyboardKey>) {
                return keyboard_function(key);
            }
            if constexpr (std::is_same_v<T, GamepadButton>) {
                return gamepad_function(key);
            }
            // std::unreachable();
        }
        [[nodiscard]] static bool is_action(Key const& key,
                                            auto mouse_function,
                                            auto keyboard_function,
                                            auto gamepad_function) {
            if (std::holds_alternative<MouseButton>(key)) {
                return mouse_function(std::get<MouseButton>(key));
            }
            if (std::holds_alternative<KeyboardKey>(key)) {
                return keyboard_function(std::get<KeyboardKey>(key));
            }
            return gamepad_function(0, std::get<GamepadButton>(key));
        }

        // --------------------------------------------------------

        template<IsKey T>
        [[nodiscard]] static bool is_down(T key) {
            return is_action(key, IsMouseButtonDown, IsKeyDown, IsGamepadButtonDown);
        }
        [[nodiscard]] static bool is_down(Key const& key) {
            return is_action(key, IsMouseButtonDown, IsKeyDown, IsGamepadButtonDown);
        }

        template<IsKey T>
        [[nodiscard]] static bool is_up(T key) {
            return is_action(key, IsMouseButtonUp, IsKeyUp, IsGamepadButtonUp);
        }
        [[nodiscard]] static bool is_up(Key const& key) {
            return is_action(key, IsMouseButtonUp, IsKeyUp, IsGamepadButtonUp);
        }

        template<IsKey T>
        [[nodiscard]] static bool is_pressed(T key) {
            return is_action(key, IsMouseButtonPressed, IsKeyPressed, IsGamepadButtonPressed);
        }
        [[nodiscard]] static bool is_pressed(Key const& key) {
            return is_action(key, IsMouseButtonPressed, IsKeyPressed, IsGamepadButtonPressed);
        }

        template<IsKey T>
        [[nodiscard]] static bool is_released(T key) {
            return is_action(key, IsMouseButtonReleased, IsKeyReleased, IsGamepadButtonReleased);
        }
        [[nodiscard]] static bool is_released(Key const& key) {
            return is_action(key, IsMouseButtonReleased, IsKeyReleased, IsGamepadButtonReleased);
        }

    public:
        [[nodiscard]] cpt::usize add_keys_to_collection(std::vector<Key> keys) {
            if (keys.empty()) {
                return 0;
            }
            auto const id = next_id();
            m_key_collections.insert({ id, std::move(keys) });
            return id;
        }
        [[nodiscard]] bool delete_key_from_collection(cpt::usize const key) {
            return m_key_collections.erase(key);
        }
        [[nodiscard]] std::vector<Key> key_from_collection(cpt::usize const key) {
            if (not m_key_collections.contains(key)) {
                return {};
            }
            return m_key_collections.at(key);
        }

        // ----------------------------------------------------------

        template<IsKey K, IsKey... M>
        [[nodiscard]] bool is_key_down(K const key, M const... modifier) const {
            if constexpr (sizeof...(modifier) == 0) {
                return is_down(key);
            } else {
                auto const result = (is_down(modifier) || ...);
                return result ? is_down(key) : false;
            }
        }

        [[nodiscard]] bool is_key_down(cpt::usize const key) const {
            if (not m_key_collections.contains(key)) {
                return false;
            }
            auto const keys = m_key_collections.at(key);
            return std::ranges::any_of(keys, [](auto const& k) { return is_down(k); });
        }
        template<IsKey... M>
        [[nodiscard]] bool is_key_down(cpt::usize const key, M const... modifier) const {
            if (not m_key_collections.contains(key)) {
                return false;
            }
            auto const keys = m_key_collections.at(key);

            if constexpr (sizeof...(modifier) == 0) {
                return std::ranges::any_of(keys, [](auto const& k) { return is_down(k); });
            } else {
                auto const result = (is_down(modifier) || ...);
                return result ? std::ranges::any_of(keys, [](auto const& k) { return is_down(k); }) : false;
            }
        }
        template<IsKey K>
        [[nodiscard]] bool is_key_down(K const key, cpt::usize const modifier) const {
            if (not m_key_collections.contains(modifier)) {
                return false;
            }
            auto const modifiers = m_key_collections.at(modifier);

            auto const result = std::ranges::any_of(modifiers, [](auto const& m) { return is_down(m); });
            return result ? is_down(key) : false;
        }
        template<std::same_as<cpt::usize>... M>
        [[nodiscard]] bool is_key_down(cpt::usize const key, M const... modifier) const {
            if (not m_key_collections.contains(key)) {
                return false;
            }
            auto const keys = m_key_collections.at(key);

            auto const modifiers = { modifier... };
            auto const result    = std::ranges::any_of(modifiers, [this](auto const& m) {
                if (not m_key_collections.contains(m)) {
                    return false;
                }
                auto const mod_keys = m_key_collections.at(m);

                return std::ranges::any_of(mod_keys, [](auto const& k) { return is_down(k); });
            });

            return result ? std::ranges::any_of(keys, [](auto const& k) { return is_down(k); }) : false;
        }
    };
} // namespace uil::global
