//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/window.hpp>

int main() {
    auto window = uil::Window({ 1280, 720 }, "ui-lib");
    window.set_draw_fps(true);

    auto window2 = std::move(window);

    while (not WindowShouldClose()) {
        window2.update();
    }
}
