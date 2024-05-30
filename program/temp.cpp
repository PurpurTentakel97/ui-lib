//
// Created by marti on 17.05.2024.
//

#include <uil/window.hpp>

int main() {
    auto window = uil::Window({ 1280, 720 }, "ui-lib");
    window.set_fps(60);
    window.set_draw_fps(true);

    while (not WindowShouldClose()) {
        window.update();
    }
}
