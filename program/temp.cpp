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
    [[maybe_unused]] auto const t1 = window.emplace_front<uil::TestScene>(1);
    [[maybe_unused]] auto const t2 = window.emplace_back<uil::TestScene>(2);
    [[maybe_unused]] auto const t3 = window.emplace_after<uil::TestScene>(t1, 3);
    [[maybe_unused]] auto const t4 = window.emplace_before<uil::TestScene>(t2,4);
    [[maybe_unused]] auto const t5 = window.emplace_at<uil::TestScene>(3,4);

    while (not WindowShouldClose()) {
        window.update();
    }
}
