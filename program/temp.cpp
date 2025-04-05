//
// Created by marti on 17.05.2024.
//

#include "test_scene.hpp"
#include "uil/global/app_context.hpp"
#include <raylib.h>
#include <uil/window.hpp>

int main() {
#ifndef NDEBUG
    auto constexpr title = "ui-lib // debug";
#else
    auto constexpr title = "ui-lib // release";
#endif

    auto config      = uil::WindowConfig();
    config.msaa      = true;
    config.resizable = true;
    config.v_sync    = true;
    config.high_dpi  = true;

    auto window = uil::Window({ 1920, 1080 }, title, config);
    window.debug_window.fps.set(true);

    [[maybe_unused]] auto const t1 = window.scene_manager().emplace_top<TestScene>(RED, Vector2{ 0.05f, 0.05f });

    auto input = uil::global::AppContext::instance().input();
    input.set_accept_keys_mouse({ MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT });
    input.set_use_one_time_input(true);

    while (not WindowShouldClose()) {
        if (input.is_accept_input_down()) {
            DrawRectangleRec(Rectangle{ 50.0f, 50.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 50.0f, 50.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_accept_input_up()) {
            DrawRectangleRec(Rectangle{ 100.0f, 50.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 100.0f, 50.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_accept_input_pressed()) {
            DrawRectangleRec(Rectangle{ 50.0f, 100.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 50.0f, 100.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_accept_input_released()) {
            DrawRectangleRec(Rectangle{ 100.0f, 100.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 100.0f, 100.0f, 50.0f, 50.0f }, RED);
        }

        if (uil::global::InputManager::is_key_down(KeyboardKey::KEY_SPACE,
                                                   uil::global::InputManager::s_shift_modifier)) {
            DrawRectangleRec(Rectangle{ 500.0f, 500.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 500.0f, 500.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_key_up(KeyboardKey::KEY_SPACE, uil::global::InputManager::s_shift_modifier)) {
            DrawRectangleRec(Rectangle{ 550.0f, 500.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 550.0f, 500.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_key_pressed(KeyboardKey::KEY_SPACE,
                                                      uil::global::InputManager::s_shift_modifier)) {
            DrawRectangleRec(Rectangle{ 500.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 500.0f, 550.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_key_released(KeyboardKey::KEY_SPACE,
                                                       uil::global::InputManager::s_shift_modifier)) {
            DrawRectangleRec(Rectangle{ 550.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 550.0f, 550.0f, 50.0f, 50.0f }, RED);
        }

        if (uil::global::InputManager::is_mouse_down(MouseButton::MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(Rectangle{ 800.0f, 500.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 800.0f, 500.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_mouse_up(MouseButton::MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(Rectangle{ 850.0f, 500.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 850.0f, 500.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_mouse_pressed(MouseButton::MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(Rectangle{ 800.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 800.0f, 550.0f, 50.0f, 50.0f }, RED);
        }
        if (uil::global::InputManager::is_mouse_released(MouseButton::MOUSE_BUTTON_LEFT)) {
            DrawRectangleRec(Rectangle{ 850.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 850.0f, 550.0f, 50.0f, 50.0f }, RED);
        }
        window.update();
    }
}
