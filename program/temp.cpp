//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/window.hpp>
#include <uil/scenes/test_scene.hpp>

int main() {
#ifndef NDEBUG
    auto constexpr title = "ui-lib // debug";
#else
    auto constexpr title = "ui-lib // release";
#endif

    auto window = uil::Window({ 1920, 1080 }, title);
    window.set_config_flag(FLAG_VSYNC_HINT, true);
    window.set_config_flag(FLAG_MSAA_4X_HINT, true);
    window.set_config_flag(FLAG_WINDOW_RESIZABLE, true);
    window.set_config_flag(FLAG_WINDOW_HIGHDPI, true);
    window.emplace_scene<uil::TestScene>(10);

    while (not WindowShouldClose()) {
        window.update();
    }
}
