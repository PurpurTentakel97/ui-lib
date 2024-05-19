//
// Created by marti on 17.05.2024.
//

#include <uil/Window.hpp>

int main() {
    auto window = std::move(uil::Window().set_resolution(uil::Resolution::HD).set_fps(60));
    while (not window.should_close()) {
        window.update();
    }
}
