//
// Created by marti on 17.05.2024.
//

#include <gtest/internal/gtest-type-util.h>
#include <raylib.h>
#include <uil/global/app_context.hpp>
#include <uil/global/input_enum.hpp>
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

    // [[maybe_unused]] auto const t1 = window.scene_manager().emplace_top<TestScene>(RED, Vector2{ 0.05f, 0.05f });


    [[maybe_unused]] auto constexpr size       = 50;
    [[maybe_unused]] auto constexpr offset     = 60;
    [[maybe_unused]] auto constexpr offset_big = 100;
    [[maybe_unused]] auto constexpr y_init     = 250;
    [[maybe_unused]] auto constexpr x_init     = 100;
    [[maybe_unused]] auto y                    = y_init;
    [[maybe_unused]] auto x                    = x_init;


    [[maybe_unused]] auto const inc_y     = [&y, offset]() { y += offset; };
    [[maybe_unused]] auto const inc_y_big = [&y, offset_big]() { y += offset_big; };
    [[maybe_unused]] auto const reset_y   = [&y, y_init]() { y = y_init; };
    [[maybe_unused]] auto const inc_x     = [&x, offset]() { x += offset; };
    [[maybe_unused]] auto const inc_x_big = [&x, offset_big]() { x += offset_big; };
    [[maybe_unused]] auto const reset_x   = [&x, x_init]() { x = x_init; };
    [[maybe_unused]] auto const reset     = [reset_x, reset_y]() {
        reset_x();
        reset_y();
    };
    [[maybe_unused]] auto const font = GetFontDefault();

    [[maybe_unused]] uil::Input_const_ref input = uil::AppContext::instance().input();

    while (not WindowShouldClose()) {


        DrawTextPro(font,
                    "is_down",
                    { static_cast<float>(x + 10), static_cast<float>(y - 20) },
                    { 0.0f, 0.0f },
                    -45.0f,
                    25.0f,
                    1.0f,
                    WHITE);
        // is_down
        input.is_down(uil::Mouse::MOUSE_BUTTON_LEFT,
                      uil::Mouse::MOUSE_BUTTON_RIGHT,
                      uil::KeyboardMod::KEY_LEFT_SHIFT,
                      uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        inc_y();
        input.is_down<uil::KeyOp::And>(uil::Mouse::MOUSE_BUTTON_LEFT,
                                       uil::Mouse::MOUSE_BUTTON_RIGHT,
                                       uil::KeyboardMod::KEY_LEFT_SHIFT,
                                       uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        reset_y();
        inc_x();


        DrawTextPro(font,
                    "is_up",
                    { static_cast<float>(x + 10), static_cast<float>(y - 20) },
                    { 0.0f, 0.0f },
                    -45.0f,
                    25.0f,
                    1.0f,
                    WHITE);
        // is_up

        input.is_up(uil::Mouse::MOUSE_BUTTON_LEFT,
                    uil::Mouse::MOUSE_BUTTON_RIGHT,
                    uil::KeyboardMod::KEY_LEFT_SHIFT,
                    uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        inc_y();


        input.is_up<uil::KeyOp::And>(uil::Mouse::MOUSE_BUTTON_LEFT,
                                     uil::Mouse::MOUSE_BUTTON_RIGHT,
                                     uil::KeyboardMod::KEY_LEFT_SHIFT,
                                     uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        reset_y();
        inc_x();


        DrawTextPro(font,
                    "is_pressed",
                    { static_cast<float>(x + 10), static_cast<float>(y - 20) },
                    { 0.0f, 0.0f },
                    -45.0f,
                    25.0f,
                    1.0f,
                    WHITE);
        // is_pressed

        input.is_pressed(uil::Mouse::MOUSE_BUTTON_LEFT,
                         uil::Mouse::MOUSE_BUTTON_RIGHT,
                         uil::KeyboardMod::KEY_LEFT_SHIFT,
                         uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        inc_y();
        input.is_pressed<uil::KeyOp::And>(uil::Mouse::MOUSE_BUTTON_LEFT,
                                          uil::Mouse::MOUSE_BUTTON_RIGHT,
                                          uil::KeyboardMod::KEY_LEFT_SHIFT,
                                          uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        reset_y();
        inc_x();


        DrawTextPro(font,
                    "is_released",
                    { static_cast<float>(x + 10), static_cast<float>(y - 20) },
                    { 0.0f, 0.0f },
                    -45.0f,
                    25.0f,
                    1.0f,
                    WHITE);
        // is_released
        input.is_released(uil::Mouse::MOUSE_BUTTON_LEFT,
                          uil::Mouse::MOUSE_BUTTON_RIGHT,
                          uil::KeyboardMod::KEY_LEFT_SHIFT,
                          uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        inc_y();
        input.is_released<uil::KeyOp::And>(uil::Mouse::MOUSE_BUTTON_LEFT,
                                           uil::Mouse::MOUSE_BUTTON_RIGHT,
                                           uil::KeyboardMod::KEY_LEFT_SHIFT,
                                           uil::KeyboardMod::KEY_RIGHT_SHIFT)
            ? DrawRectangle(x, y, size, size, GREEN)
            : DrawRectangle(x, y, size, size, RED);
        reset_y();
        inc_x();

        reset();
        window.update();
    }
}
