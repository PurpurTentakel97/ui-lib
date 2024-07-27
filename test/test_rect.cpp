//
// Purpur Tentakel
// 27.05.24
//

#include <array>
#include <cpt/vec2.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <uil/exception.hpp>
#include <uil/h_rect.hpp>


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

class PointAndSizeFromRectFixtures : public testing::TestWithParam<Rectangle> { };

TEST_P(PointAndSizeFromRectFixtures, Succsess) {
    auto const rect = GetParam();

    auto const point_result = uil::point_from_rect(rect);
    auto const size_result  = uil::size_from_rect(rect);

    EXPECT_FLOAT_EQ(rect.x, point_result.x);
    EXPECT_FLOAT_EQ(rect.y, point_result.y);
    EXPECT_FLOAT_EQ(rect.width, size_result.x);
    EXPECT_FLOAT_EQ(rect.height, size_result.y);
}

INSTANTIATE_TEST_SUITE_P(Rectangle,
                         PointAndSizeFromRectFixtures,
                         ::testing::Values(Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f },
                                           Rectangle{ 0.1f, 0.2f, 0.3f, 0.4f },
                                           Rectangle{ 1.0f, -2.0f, 10000.0f, 0.00052641f }));

class RectFromPointAndSize : public testing::TestWithParam<std::tuple<Vector2, Vector2>> { };

TEST_P(RectFromPointAndSize, Success) {
    auto const point = std::get<0>(GetParam());
    auto const size  = std::get<1>(GetParam());

    auto const rect_result = uil::rect_from_point_and_size(point, size);

    EXPECT_FLOAT_EQ(point.x, rect_result.x);
    EXPECT_FLOAT_EQ(point.y, rect_result.y);
    EXPECT_FLOAT_EQ(size.x, rect_result.width);
    EXPECT_FLOAT_EQ(size.y, rect_result.height);
}


INSTANTIATE_TEST_SUITE_P(Rectangle,
                         RectFromPointAndSize,
                         ::testing::Values(std::make_tuple(Vector2{ 0.5f, 0.5f }, Vector2{ 0.5f, 0.5f }),
                                           std::make_tuple(Vector2{ 0.1f, 0.2f }, Vector2{ 0.3f, 0.4f }),
                                           std::make_tuple(Vector2{ -0.1f, -0.2f }, Vector2{ -0.3f, -0.4f })));
