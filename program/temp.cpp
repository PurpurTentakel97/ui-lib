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

    auto window = uil::Window({ 1920, 1080 }, title, config);
    window.emplace_scene<uil::TestScene>(1);
    window.emplace_scene<uil::TestScene>(2);
    window.emplace_scene<uil::TestScene>(3);
    window.emplace_scene<uil::TestScene>(4);

    while (not WindowShouldClose()) {
        window.update();
    }
}
