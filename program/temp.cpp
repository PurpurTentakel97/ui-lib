//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/window.hpp>

int main() {
    auto window = uil::Window({ 1920, 1080 }, "ui-lib");
    window.set_config_flag(FLAG_VSYNC_HINT, true);
    window.set_config_flag(FLAG_MSAA_4X_HINT, true);
    window.set_config_flag(FLAG_WINDOW_RESIZABLE, true);
    window.set_config_flag(FLAG_WINDOW_HIGHDPI, true);
    window.set_draw_fps(true);

    while (not WindowShouldClose()) {
        window.update();
    }
}
