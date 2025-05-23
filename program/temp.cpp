//
// Created by marti on 17.05.2024.
//

#include <raylib.h>
#include <uil/window.hpp>
#include "input_test_scene.hpp"
#include "music_test_scene.hpp"
#include "asset_test_scene.hpp"

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
    window.debug_window.fps.set(true);

    // [[maybe_unused]] auto const t1 = window.scene_manager().emplace_top<InputTestScene>();
    [[maybe_unused]] auto const t2 = window.scene_manager().emplace_top<MusicTestScene>();
    // [[maybe_unused]] auto const t3 = window.scene_manager().emplace_top<AssetTestScene>();
    while (not WindowShouldClose()) {
        window.update();
    }
}
