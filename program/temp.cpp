//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/scenes/test_scene.hpp>
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

    auto window                    = uil::Window({ 1920, 1080 }, title, config);

    [[maybe_unused]] auto const t1 = window.scene_manager().emplace_top<uil::TestScene>(RED, Vector2{ 0.05f, 0.05f });
    [[maybe_unused]] auto const t2 = window.scene_manager().emplace_top<uil::TestScene>(BLUE, Vector2{ 0.1f, 0.1f });
    [[maybe_unused]] auto const t3 = window.scene_manager().emplace_top<uil::TestScene>(GREEN, Vector2{ 0.15f, 0.15f });
    [[maybe_unused]] auto const t4 = window.scene_manager().emplace_top<uil::TestScene>(PINK, Vector2{ 0.2f, 0.2f });
    [[maybe_unused]] auto const t5 = window.scene_manager().emplace_top<uil::TestScene>(WHITE, Vector2{ 0.25f, 0.25f });

    while (not WindowShouldClose()) {
        window.update();
    }
}
