//
// Created by marti on 17.05.2024.
//

#include "test_scene.hpp"
#include "uil/global/app_context.hpp"
#include <raylib.h>
#include <uil/window.hpp>
#include <iostream>

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

    auto const& input                   = uil::global::AppContext::instance().input();
    [[maybe_unused]] auto const up_keys = uil::global::AppContext::instance().input().add_keys_to_collection(
            { KEY_W, GAMEPAD_BUTTON_LEFT_FACE_UP });
    [[maybe_unused]] auto const shift_modifiers
            = uil::global::AppContext::instance().input().add_keys_to_collection({ KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT });

    std::cout << up_keys << " | " << shift_modifiers << "\n";

    while (not WindowShouldClose()) {

        if (input.is_key_down(KEY_W)) {
            DrawRectangleRec(Rectangle{ 800.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 800.0f, 550.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_key_down(KEY_W, MOUSE_BUTTON_LEFT, KEY_LEFT_SHIFT)) {
            DrawRectangleRec(Rectangle{ 850.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 850.0f, 550.0f, 50.0f, 50.0f }, RED);
        }

        if (input.is_key_down(up_keys)) {
            DrawRectangleRec(Rectangle{ 800.0f, 700.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 800.0f, 700.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_key_down(up_keys, MOUSE_BUTTON_LEFT, KEY_LEFT_SHIFT)) {
            DrawRectangleRec(Rectangle{ 850.0f, 700.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 850.0f, 700.0f, 50.0f, 50.0f }, RED);
        }

        if (input.is_key_down(KEY_W)) {
            DrawRectangleRec(Rectangle{ 1000.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 1000.0f, 550.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_key_down(KEY_W, shift_modifiers)) {
            DrawRectangleRec(Rectangle{ 1050.0f, 550.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 1050.0f, 550.0f, 50.0f, 50.0f }, RED);
        }

        if (input.is_key_down(up_keys)) {
            DrawRectangleRec(Rectangle{ 1000.0f, 700.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 1000.0f, 700.0f, 50.0f, 50.0f }, RED);
        }
        if (input.is_key_down(up_keys, shift_modifiers)) {
            DrawRectangleRec(Rectangle{ 1050.0f, 700.0f, 50.0f, 50.0f }, GREEN);
        } else {
            DrawRectangleRec(Rectangle{ 1050.0f, 700.0f, 50.0f, 50.0f }, RED);
        }

        window.update();
    }
}
