//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/global/app_context.hpp>
#include <uil/window.hpp>
#include "input_test_scene.hpp"

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

    [[maybe_unused]] auto const t1 = window.scene_manager().emplace_top<InputTestScene>();

    [[maybe_unused]] auto& app_context = uil::AppContext::instance();
    [[maybe_unused]] auto& sound       = app_context.sound();

    cpt::usize id{0};
    [[maybe_unused]] auto const test   = sound.load_sound(id, "/assets/sounds/clicked_accepted_std.mp3", 30);

    sound.set_level(0, 0.5f);
    auto level = 1.0f;
    sound.set_level(1, 1.0f);

    sound.link_sound_to_level(id, 1);


    while (not WindowShouldClose()) {
        window.update();
    }
}
