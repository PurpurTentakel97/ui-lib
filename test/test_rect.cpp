//
// Purpur Tentakel
// 27.05.24
//

#include <array>
#include <cpt/vec2.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <uil/exception.hpp>
#include <uil/helper_rect.hpp>


TEST(Collider, Exception) {
    auto constexpr relative    = Rectangle{ 0.1f, 0.1f, 0.1f, 0.1f };
    auto constexpr resolutions = std::array<cpt::Vec2_i, 3>{
        { { 0, 1 }, { 1, 0 }, { 0, 0 } }
    };

    for (auto const& resolution : resolutions) {
        try {
            [[maybe_unused]] auto const result = uil::relative_from_collider(relative, resolution);
            GTEST_FAIL() << "exception uil::DivideByZero not thrown";
        } catch (uil::DivideByZero const& e) { EXPECT_STREQ(e.what(), "resolution width or height was zero"); }
    }
}

class ColiderFixtures : public testing::TestWithParam<std::tuple<Rectangle, cpt::Vec2_i, Rectangle>> { };

TEST_P(ColiderFixtures, ColiderFromRelative) {
    auto const relative   = std::get<0>(GetParam());
    auto const resolution = std::get<1>(GetParam());
    auto const expected   = std::get<2>(GetParam());
    auto const result     = uil::collider_from_relative(relative, resolution);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
    EXPECT_FLOAT_EQ(expected.width, result.width);
    EXPECT_FLOAT_EQ(expected.height, result.height);
}

TEST_P(ColiderFixtures, RelativeFromColider) {
    auto const collider   = std::get<2>(GetParam());
    auto const resolution = std::get<1>(GetParam());
    auto const expected   = std::get<0>(GetParam());
    auto const result     = uil::relative_from_collider(collider, resolution);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
    EXPECT_FLOAT_EQ(expected.width, result.width);
    EXPECT_FLOAT_EQ(expected.height, result.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         ColiderFixtures,
                         ::testing::Values(std::make_tuple(Rectangle{ 1.0f, 1.0f, 1.0f, 1.0f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 1000.0f, 1000.0f, 1000.0f, 1000.0f }),
                                           std::make_tuple(Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 500.0f, 500.0f, 500.0f, 500.0f }),
                                           std::make_tuple(Rectangle{ 0.5f, 1.0f, 1.0f, 1.0f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 500.0f, 1000.0f, 1000.0f, 1000.0f }),
                                           std::make_tuple(Rectangle{ 1.0f, 0.5f, 1.0f, 1.0f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 1000.0f, 500.0f, 1000.0f, 1000.0f }),
                                           std::make_tuple(Rectangle{ 1.0f, 1.0f, 0.5f, 1.0f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 1000.0f, 1000.0f, 500.0f, 1000.0f }),
                                           std::make_tuple(Rectangle{ 1.0f, 1.0f, 1.0f, 0.5f },
                                                           cpt::Vec2_i{ 1000, 1000 },
                                                           Rectangle{ 1000.0f, 1000.0f, 1000.0f, 500.0f })));
