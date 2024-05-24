//
// Purpur Tentakel
// 24.05.24
//

#include <gtest/gtest.h>
#include <uil/window.hpp>

TEST(Window, CreateWithUsize) {
    auto const window = uil::Window({ 1920, 1080 }, "test");
    EXPECT_EQ(window.resolution(), uil::Resolution::CUSTOM);
    EXPECT_EQ(window.resolution_usize().x, 1920);
    EXPECT_EQ(window.resolution_usize().y, 1080);
}

TEST(Window, CreateWithEnum) {
    auto const window = uil::Window(uil::Resolution::FULL_HD, "test");
    EXPECT_EQ(window.resolution(), uil::Resolution::FULL_HD);
    EXPECT_EQ(window.resolution_usize().x, 1920);
    EXPECT_EQ(window.resolution_usize().y, 1080);
}

TEST(Window, CreateAndUpdate) {
    auto window = uil::Window(uil::Resolution::FULL_HD, "test");

    for (auto i = 0; i < 100; ++i) {
        window.update();
    }
}

TEST(Window, SetResolutionUsize) {
    auto window = uil::Window(uil::Resolution::HD, "test").set_resolution({ 640, 480 });
    EXPECT_EQ(window.resolution(), uil::Resolution::CUSTOM);
    EXPECT_EQ(window.resolution_usize().x, 640);
    EXPECT_EQ(window.resolution_usize().y, 480);

    window.set_resolution({ 1920, 1080 });
    EXPECT_EQ(window.resolution(), uil::Resolution::CUSTOM);
    EXPECT_EQ(window.resolution_usize().x, 1920);
    EXPECT_EQ(window.resolution_usize().y, 1080);
}

TEST(Window, SetResolutionEnum) {
    auto window = uil::Window(uil::Resolution::HD, "test").set_resolution(uil::Resolution::VGA);
    EXPECT_EQ(window.resolution(), uil::Resolution::VGA);
    EXPECT_EQ(window.resolution_usize().x, 640);
    EXPECT_EQ(window.resolution_usize().y, 480);

    window.set_resolution(uil::Resolution::FULL_HD);
    EXPECT_EQ(window.resolution(), uil::Resolution::FULL_HD);
    EXPECT_EQ(window.resolution_usize().x, 1920);
    EXPECT_EQ(window.resolution_usize().y, 1080);
}

TEST(Window, SetFPS) {
    auto window = uil::Window(uil::Resolution::HD, "test").set_fps(30);
    EXPECT_EQ(window.fps(), 30);

    window.set_fps(120);
    EXPECT_EQ(window.fps(), 120);
}

TEST(Window, SetDrawFPS) {
    auto window = uil::Window(uil::Resolution::HD, "test").set_draw_fps(true);
    EXPECT_EQ(window.draw_fps(), true);

    window.set_draw_fps(false);
    EXPECT_EQ(window.draw_fps(), false);
}
