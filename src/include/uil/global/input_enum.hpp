//
// Purpur Tentakel
// 27.05.2025
// AUTOGENERATED: Do not modify this file
//

#pragma once

#include <concepts>
#include <raylib.h>

namespace uil {

// ---------- Keyboard ----------
	#define KEYBOARD_KEY_LIST \
		K(KEY_NULL) \
		K(KEY_APOSTROPHE) \
		K(KEY_COMMA) \
		K(KEY_MINUS) \
		K(KEY_PERIOD) \
		K(KEY_SLASH) \
		K(KEY_ZERO) \
		K(KEY_ONE) \
		K(KEY_TWO) \
		K(KEY_THREE) \
		K(KEY_FOUR) \
		K(KEY_FIVE) \
		K(KEY_SIX) \
		K(KEY_SEVEN) \
		K(KEY_EIGHT) \
		K(KEY_NINE) \
		K(KEY_SEMICOLON) \
		K(KEY_EQUAL) \
		K(KEY_A) \
		K(KEY_B) \
		K(KEY_C) \
		K(KEY_D) \
		K(KEY_E) \
		K(KEY_F) \
		K(KEY_G) \
		K(KEY_H) \
		K(KEY_I) \
		K(KEY_J) \
		K(KEY_K) \
		K(KEY_L) \
		K(KEY_M) \
		K(KEY_N) \
		K(KEY_O) \
		K(KEY_P) \
		K(KEY_Q) \
		K(KEY_R) \
		K(KEY_S) \
		K(KEY_T) \
		K(KEY_U) \
		K(KEY_V) \
		K(KEY_W) \
		K(KEY_X) \
		K(KEY_Y) \
		K(KEY_Z) \
		K(KEY_LEFT_BRACKET) \
		K(KEY_BACKSLASH) \
		K(KEY_RIGHT_BRACKET) \
		K(KEY_GRAVE) \
		K(KEY_SPACE) \
		K(KEY_ESCAPE) \
		K(KEY_ENTER) \
		K(KEY_TAB) \
		K(KEY_BACKSPACE) \
		K(KEY_INSERT) \
		K(KEY_DELETE) \
		K(KEY_RIGHT) \
		K(KEY_LEFT) \
		K(KEY_DOWN) \
		K(KEY_UP) \
		K(KEY_PAGE_UP) \
		K(KEY_PAGE_DOWN) \
		K(KEY_HOME) \
		K(KEY_END) \
		K(KEY_CAPS_LOCK) \
		K(KEY_SCROLL_LOCK) \
		K(KEY_NUM_LOCK) \
		K(KEY_PRINT_SCREEN) \
		K(KEY_PAUSE) \
		K(KEY_F1) \
		K(KEY_F2) \
		K(KEY_F3) \
		K(KEY_F4) \
		K(KEY_F5) \
		K(KEY_F6) \
		K(KEY_F7) \
		K(KEY_F8) \
		K(KEY_F9) \
		K(KEY_F10) \
		K(KEY_F11) \
		K(KEY_F12) \
		K(KEY_LEFT_SHIFT) \
		K(KEY_LEFT_CONTROL) \
		K(KEY_LEFT_ALT) \
		K(KEY_LEFT_SUPER) \
		K(KEY_RIGHT_SHIFT) \
		K(KEY_RIGHT_CONTROL) \
		K(KEY_RIGHT_ALT) \
		K(KEY_RIGHT_SUPER) \
		K(KEY_KB_MENU) \
		K(KEY_KP_0) \
		K(KEY_KP_1) \
		K(KEY_KP_2) \
		K(KEY_KP_3) \
		K(KEY_KP_4) \
		K(KEY_KP_5) \
		K(KEY_KP_6) \
		K(KEY_KP_7) \
		K(KEY_KP_8) \
		K(KEY_KP_9) \
		K(KEY_KP_DECIMAL) \
		K(KEY_KP_DIVIDE) \
		K(KEY_KP_MULTIPLY) \
		K(KEY_KP_SUBTRACT) \
		K(KEY_KP_ADD) \
		K(KEY_KP_ENTER) \
		K(KEY_KP_EQUAL) \
		K(KEY_BACK) \
		K(KEY_MENU) \
		K(KEY_VOLUME_UP) \
		K(KEY_VOLUME_DOWN)

	enum class Keyboard {
	#define K(name) name = static_cast<int>(KeyboardKey::name),
		KEYBOARD_KEY_LIST
	#undef K
	};

	enum class KeyboardMod {
	#define K(name) name = static_cast<int>(KeyboardKey::name),
		KEYBOARD_KEY_LIST
	#undef K
	};

	#undef KEYBOARD_KEY_LIST

// ---------- Mouse ----------
	#define MOUSE_BUTTON_LIST \
		M(MOUSE_BUTTON_LEFT) \
		M(MOUSE_BUTTON_RIGHT) \
		M(MOUSE_BUTTON_MIDDLE) \
		M(MOUSE_BUTTON_SIDE) \
		M(MOUSE_BUTTON_EXTRA) \
		M(MOUSE_BUTTON_FORWARD) \
		M(MOUSE_BUTTON_BACK)

	enum class Mouse {
	#define M(name) name = static_cast<int>(MouseButton::name),
		MOUSE_BUTTON_LIST
	#undef M
	};

	enum class MouseMod {
	#define M(name) name = static_cast<int>(MouseButton::name),
		MOUSE_BUTTON_LIST
	#undef M
	};

	#undef MOUSE_BUTTON_LIST

// ---------- Gamepad ----------
	#define GAME_PAD_KEY_LIST \
		G(GAMEPAD_BUTTON_UNKNOWN) \
		G(GAMEPAD_BUTTON_LEFT_FACE_UP) \
		G(GAMEPAD_BUTTON_LEFT_FACE_RIGHT) \
		G(GAMEPAD_BUTTON_LEFT_FACE_DOWN) \
		G(GAMEPAD_BUTTON_LEFT_FACE_LEFT) \
		G(GAMEPAD_BUTTON_RIGHT_FACE_UP) \
		G(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) \
		G(GAMEPAD_BUTTON_RIGHT_FACE_DOWN) \
		G(GAMEPAD_BUTTON_RIGHT_FACE_LEFT) \
		G(GAMEPAD_BUTTON_LEFT_TRIGGER_1) \
		G(GAMEPAD_BUTTON_LEFT_TRIGGER_2) \
		G(GAMEPAD_BUTTON_RIGHT_TRIGGER_1) \
		G(GAMEPAD_BUTTON_RIGHT_TRIGGER_2) \
		G(GAMEPAD_BUTTON_MIDDLE_LEFT) \
		G(GAMEPAD_BUTTON_MIDDLE) \
		G(GAMEPAD_BUTTON_MIDDLE_RIGHT) \
		G(GAMEPAD_BUTTON_LEFT_THUMB) \
		G(GAMEPAD_BUTTON_RIGHT_THUMB)

	enum class Gamepad {
	#define G(name) name = static_cast<int>(GamepadButton::name),
		GAME_PAD_KEY_LIST
	#undef G
	};

	enum class GamepadMod {
	#define G(name) name = static_cast<int>(GamepadButton::name),
		GAME_PAD_KEY_LIST
	#undef G
	};

	#undef GAME_PAD_KEY_LIST

// ---------- Concepts ----------
	template <typename T>
    concept IsRayKey =
        std::is_same_v<T, KeyboardKey> or
        std::is_same_v<T, MouseButton> or
        std::is_same_v<T, GamepadButton>;

    template <typename T>
    concept IsButton =
        std::is_same_v<T, Keyboard> or
        std::is_same_v<T, Mouse> or
        std::is_same_v<T, Gamepad>;

    template <typename T>
    concept IsModifier =
        std::is_same_v<T, KeyboardMod> or
        std::is_same_v<T, MouseMod> or
        std::is_same_v<T, GamepadMod>;

    template <typename T>
    concept IsInput =
        IsButton<T> or
        IsModifier<T>;

} // namespace uil

// fully generated
