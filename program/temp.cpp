//
// Created by marti on 17.05.2024.
//

#include "asset_test_scene.hpp"
#include "focus_test_scene.hpp"
#include "font_test_scene.hpp"
#include "input_test_scene.hpp"
#include "music_test_scene.hpp"
#include <raylib.h>
#include <uil/window.hpp>

int main() {
#ifndef NDEBUG
    auto constexpr title = "ui-lib // debug";
    cpt::log::set_level(cpt::log::Level::Trace);
#else
    auto constexpr title = "ui-lib // release";
    cpt::log::set_level(cpt::log::Level::Error);
#endif

    auto config      = uil::WindowConfig();
    config.msaa      = true;
    config.resizable = true;
    config.v_sync    = true;
    config.high_dpi  = true;

    auto window = uil::Window(title, config);
    uil::AppContext::instance().resolution().set_resolution(uil::Resolution::FULL_HD);
    window.debug_window.fps.set(true);
    window.debug_window.mouse.set(true);

    // auto const t1 = window.scene_manager().emplace_top<InputTestScene>();
    // auto const t2 = window.scene_manager().emplace_top<MusicTestScene>();
    // auto const t3 = window.scene_manager().emplace_top<AssetTestScene>();
    // auto const t4 = window.scene_manager().emplace_top<FontTestScene>();
    auto const t5 = window.scene_manager().emplace_top<FocusTestScene>();
    while (not WindowShouldClose()) {
        window.update();
    }
}
