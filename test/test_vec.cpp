//
// Purpur Tentakel
// 12.07.24
//

#include "uil/exception.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <uil/helper_vec.hpp>

class Vector2MagnetudeFixtures : public testing::TestWithParam<std::tuple<Vector2, float>> { };

TEST_P(Vector2MagnetudeFixtures, Success) {
    auto const vec = std::get<0>(GetParam());
    auto const mag = std::get<1>(GetParam());

    auto const result = uil::magnitude(vec);

    EXPECT_FLOAT_EQ(mag, result);
}

INSTANTIATE_TEST_SUITE_P(VECTOR2,
                         Vector2MagnetudeFixtures,
                         ::testing::Values(std::make_tuple(Vector2(1.0f, 1.0f), 1.4142135f),
                                           std::make_tuple(Vector2(-1.0f, 1.0f), 1.4142135f),
                                           std::make_tuple(Vector2(1.0f, -1.0f), 1.4142135f),
                                           std::make_tuple(Vector2(-1.0f, -1.0f), 1.4142135f),
                                           std::make_tuple(Vector2(2.0f, 1.0f), 2.2360679f)));

class Vecor2NormalizeFixtures : public testing::TestWithParam<std::tuple<Vector2, Vector2>> { };

TEST_P(Vecor2NormalizeFixtures, Success) {
    auto const vec        = std::get<0>(GetParam());
    auto const expected   = std::get<1>(GetParam());
    auto constexpr length = 1.0f;

    auto const result = uil::normalize(vec);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
    EXPECT_FLOAT_EQ(length, uil::magnitude(result));
}

INSTANTIATE_TEST_SUITE_P(VECTOR2,
                         Vecor2NormalizeFixtures,
                         testing::Values(std::make_tuple(Vector2(1.0f, 1.0f), Vector2(0.70710677f, 0.70710677f)),
                                         std::make_tuple(Vector2(1.0f, 0.0f), Vector2(1.0f, 0.0f)),
                                         std::make_tuple(Vector2(0.0f, 1.0f), Vector2(0.0f, 1.0f)),
                                         std::make_tuple(Vector2(2.0f, 1.0f), Vector2(0.8944272f, 0.4472136f))));

TEST(Vector2, DevideByZeroExpection) {
    auto constexpr vec = Vector2{ 0.0f, 0.0f };

    try {
        [[maybe_unused]] auto const result = uil::normalize(vec);
        GTEST_FAIL() << "DevideByZero not thrown";
    } catch (uil::DivideByZero const& e) { EXPECT_STREQ(e.what(), "Devide by 0.0f while normalize a Vector2"); }
}
