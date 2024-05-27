//
// Purpur Tentakel
// 27.05.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/resolution.hpp>

class ResolutionFixture : public testing::TestWithParam<std::tuple<uil::Resolution, cpt::Vec2_i>> { };

TEST_P(ResolutionFixture, VecFromResolution) {
    auto const resolution = std::get<0>(GetParam());
    auto const expected   = std::get<1>(GetParam());
    auto const result     = uil::vec_from_resolution(resolution, { 1, 1 });

    EXPECT_EQ(expected.x, result.x);
    EXPECT_EQ(expected.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         ResolutionFixture,
                         ::testing::Values(std::make_tuple(uil::Resolution::UHD2, cpt::Vec2_i{ 7680, 4320 }),
                                           std::make_tuple(uil::Resolution::UHD1, cpt::Vec2_i{ 3840, 2160 }),
                                           std::make_tuple(uil::Resolution::QUAD_HD, cpt::Vec2_i{ 2560, 1440 }),
                                           std::make_tuple(uil::Resolution::FULL_HD, cpt::Vec2_i{ 1920, 1080 }),
                                           std::make_tuple(uil::Resolution::HD, cpt::Vec2_i{ 1280, 720 }),
                                           std::make_tuple(uil::Resolution::SD_3, cpt::Vec2_i{ 854, 480 }),
                                           std::make_tuple(uil::Resolution::SD_2, cpt::Vec2_i{ 640, 360 }),
                                           std::make_tuple(uil::Resolution::SD_1, cpt::Vec2_i{ 426, 240 }),

                                           std::make_tuple(uil::Resolution::_5K_ULTRA_WIDE, cpt::Vec2_i{ 5120, 2160 }),
                                           std::make_tuple(uil::Resolution::UWQHD, cpt::Vec2_i{ 3440, 1440 }),
                                           std::make_tuple(uil::Resolution::UWHD, cpt::Vec2_i{ 2560, 1440 }),

                                           std::make_tuple(uil::Resolution::QXGA, cpt::Vec2_i{ 2048, 1536 }),
                                           std::make_tuple(uil::Resolution::UXGA, cpt::Vec2_i{ 1600, 1200 }),
                                           std::make_tuple(uil::Resolution::XGA, cpt::Vec2_i{ 1024, 768 }),
                                           std::make_tuple(uil::Resolution::SVGA, cpt::Vec2_i{ 800, 600 }),
                                           std::make_tuple(uil::Resolution::PAL, cpt::Vec2_i{ 720, 576 }),
                                           std::make_tuple(uil::Resolution::VGA, cpt::Vec2_i{ 640, 480 }),

                                           std::make_tuple(uil::Resolution::CUSTOM, cpt::Vec2_i{ 1, 1 })));
