//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/window.hpp>

int main() {
#ifdef _DEBUG
    auto constexpr title = "ui-lib // debug";
#else
    auto constexpr title = "ui-lib // release";
#endif

    auto window = uil::Window({ 1920, 1080 }, title);
    window.set_config_flag(FLAG_VSYNC_HINT, true);
    window.set_config_flag(FLAG_MSAA_4X_HINT, true);
    window.set_config_flag(FLAG_WINDOW_RESIZABLE, true);
    window.set_config_flag(FLAG_WINDOW_HIGHDPI, true);

    while (not WindowShouldClose()) {
        window.update();
    }
}
