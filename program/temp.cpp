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

    auto window = uil::Window({ 1920, 1080 }, title, config);

    [[maybe_unused]] auto const t1 = window.scene_manager().emplace_front<uil::TestScene>(1);
    [[maybe_unused]] auto const t2 = window.scene_manager().emplace_front<uil::TestScene>(2);
    [[maybe_unused]] auto const t3 = window.scene_manager().emplace_front<uil::TestScene>(3);
    [[maybe_unused]] auto const t4 = window.scene_manager().emplace_front<uil::TestScene>(4);
    [[maybe_unused]] auto const t5 = window.scene_manager().emplace_front<uil::TestScene>(1);
    [[maybe_unused]] auto const t6 = window.scene_manager().emplace_front<uil::TestScene>(2);
    [[maybe_unused]] auto const t7 = window.scene_manager().emplace_front<uil::TestScene>(3);
    [[maybe_unused]] auto const t8 = window.scene_manager().emplace_front<uil::TestScene>(4);

    [[maybe_unused]] auto s1 = window.scene_manager().pop_back(); // t1
    window.scene_manager().push_back(std::move(s1));

    [[maybe_unused]] auto s2 = window.scene_manager().pop_front(); // t8
    window.scene_manager().push_front(std::move(s2));

    [[maybe_unused]] auto s3 = window.scene_manager().pop_at(2); // t3
    window.scene_manager().push_at(2, std::move(s3));

    [[maybe_unused]] auto s4 = window.scene_manager().pop_before(t6); // t7
    window.scene_manager().push_before(t6,std::move(s4));

    [[maybe_unused]] auto s5 = window.scene_manager().pop_after(t6); // t5
    window.scene_manager().push_after(t6,std::move(s5));

    [[maybe_unused]] auto s6 = window.scene_manager().pop_this(t6); // t6
    window.scene_manager().push_at(5,std::move(s6));

    window.scene_manager().erase_back();     // t1
    window.scene_manager().erase_front();    // t8
    window.scene_manager().erase_at(2);      // t4
    window.scene_manager().erase_after(t3);  // t2
    window.scene_manager().erase_before(t6); // t7
    window.scene_manager().erase_this(t3);   // t3


    while (not WindowShouldClose()) {
        window.update();
    }
}
