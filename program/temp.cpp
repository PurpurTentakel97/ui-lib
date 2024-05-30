//
// Created by marti on 17.05.2024.
//

#include <uil/window.hpp>
#include <iostream>
int main() {
    auto window = uil::Window({ 1280, 720 }, "ui-lib").set_fps(60).set_draw_fps(true);
    while (not window.should_close()) {
        window.update();
    }
}
