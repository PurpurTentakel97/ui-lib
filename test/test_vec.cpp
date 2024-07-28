//
// Purpur Tentakel
// 12.07.24
//

#include "uil/exception.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <uil/helper/vec.hpp>

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

TEST(Vector2, DevideByZeroExpectionNormalize) {
    auto constexpr vec = Vector2{ 0.0f, 0.0f };

    try {
        [[maybe_unused]] auto const result = uil::normalize(vec);
        GTEST_FAIL() << "DevideByZero not thrown";
    } catch (uil::DivideByZero const& e) { EXPECT_STREQ(e.what(), "Devide by 0.0f while normalize a Vector2"); }
}

class Vector2OperatorPlusFixures : public testing::TestWithParam<std::tuple<Vector2, Vector2, Vector2>> { };

TEST_P(Vector2OperatorPlusFixures, Succsess) {
    auto const vec_c    = std::get<0>(GetParam());
    auto vec_m          = std::get<0>(GetParam());
    auto const to_add   = std::get<1>(GetParam());
    auto const expected = std::get<2>(GetParam());

    auto const result = vec_c + to_add;
    vec_m += to_add;

    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(vec_m.x, expected.x);
    EXPECT_FLOAT_EQ(vec_m.y, expected.y);
}

INSTANTIATE_TEST_SUITE_P(
        VECTOR2,
        Vector2OperatorPlusFixures,
        ::testing::Values(std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ 1.0f, 1.0f }, Vector2{ 2.0f, 2.0f }),
                          std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ -1.0f, -1.0f }, Vector2{ 0.0f, 0.0f }),
                          std::make_tuple(Vector2{ -1.0f, -1.0f }, Vector2{ 1.0f, 1.0f }, Vector2{ 0.0f, 0.0f }),
                          std::make_tuple(Vector2{ -1.0f, -1.0f }, Vector2{ -1.0f, -1.0f }, Vector2{ -2.0f, -2.0f }),
                          std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ 0.0f, 0.0f }, Vector2{ 1.0f, 1.0f })));

class Vector2OperatorMinusFixtures : public testing::TestWithParam<std::tuple<Vector2, Vector2, Vector2>> { };

TEST_P(Vector2OperatorMinusFixtures, Succsess) {
    auto const vec_c    = std::get<0>(GetParam());
    auto vec_m          = std::get<0>(GetParam());
    auto const to_sub   = std::get<1>(GetParam());
    auto const expected = std::get<2>(GetParam());

    auto const result = vec_c - to_sub;
    vec_m -= to_sub;

    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(vec_m.x, expected.x);
    EXPECT_FLOAT_EQ(vec_m.y, expected.y);
}

INSTANTIATE_TEST_SUITE_P(
        VECTOR2,
        Vector2OperatorMinusFixtures,
        ::testing::Values(std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ 1.0f, 1.0f }, Vector2{ 0.0f, 0.0f }),
                          std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ -1.0f, -1.0f }, Vector2{ 2.0f, 2.0f }),
                          std::make_tuple(Vector2{ -1.0f, -1.0f }, Vector2{ 1.0f, 1.0f }, Vector2{ -2.0f, -2.0f }),
                          std::make_tuple(Vector2{ -1.0f, -1.0f }, Vector2{ -1.0f, -1.0f }, Vector2{ 0.0f, 0.0f }),
                          std::make_tuple(Vector2{ 1.0f, 1.0f }, Vector2{ 0.0f, 0.0f }, Vector2{ 1.0f, 1.0f })));

class Vector2OperatorMultiplyFixtures : public testing::TestWithParam<std::tuple<Vector2, float, Vector2>> { };

TEST_P(Vector2OperatorMultiplyFixtures, Succsess) {
    auto const vec_c       = std::get<0>(GetParam());
    auto vec_m             = std::get<0>(GetParam());
    auto const to_multiply = std::get<1>(GetParam());
    auto const expected    = std::get<2>(GetParam());

    auto const result = vec_c * to_multiply;
    vec_m *= to_multiply;

    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(vec_m.x, expected.x);
    EXPECT_FLOAT_EQ(vec_m.y, expected.y);
}

INSTANTIATE_TEST_SUITE_P(VECTOR2,
                         Vector2OperatorMultiplyFixtures,
                         ::testing::Values(std::make_tuple(Vector2{ 1.0f, 1.0f }, 2.0f, Vector2{ 2.0f, 2.0f }),
                                           std::make_tuple(Vector2{ 1.0f, 1.0f }, -2.0f, Vector2{ -2.0f, -2.0f }),
                                           std::make_tuple(Vector2{ -1.0f, -1.0f }, 2.0f, Vector2{ -2.0f, -2.0f }),
                                           std::make_tuple(Vector2{ -1.0f, -1.0f }, -2.0f, Vector2{ 2.0f, 2.0f }),
                                           std::make_tuple(Vector2{ 1.0f, 1.0f }, 1.0f, Vector2{ 1.0f, 1.0f }),
                                           std::make_tuple(Vector2{ 1.0f, 1.0f }, 0.0f, Vector2{ 0.0f, 0.0f })));

class Vector2OperatorDivideFixtures : public testing::TestWithParam<std::tuple<Vector2, float, Vector2>> { };

TEST_P(Vector2OperatorDivideFixtures, Succsess) {
    auto const vec_c     = std::get<0>(GetParam());
    auto vec_m           = std::get<0>(GetParam());
    auto const to_divide = std::get<1>(GetParam());
    auto const expected  = std::get<2>(GetParam());

    auto const result = vec_c / to_divide;
    vec_m /= to_divide;

    EXPECT_FLOAT_EQ(result.x, expected.x);
    EXPECT_FLOAT_EQ(result.y, expected.y);
    EXPECT_FLOAT_EQ(vec_m.x, expected.x);
    EXPECT_FLOAT_EQ(vec_m.y, expected.y);
}


INSTANTIATE_TEST_SUITE_P(VECTOR2,
                         Vector2OperatorDivideFixtures,
                         ::testing::Values(std::make_tuple(Vector2{ 1.0f, 1.0f }, 2.0f, Vector2{ 0.5f, 0.5f }),
                                           std::make_tuple(Vector2{ 1.0f, 1.0f }, -2.0f, Vector2{ -0.5f, -0.5f }),
                                           std::make_tuple(Vector2{ -1.0f, -1.0f }, 2.0f, Vector2{ -0.5f, -0.5f }),
                                           std::make_tuple(Vector2{ -1.0f, -1.0f }, -2.0f, Vector2{ 0.5f, 0.5f }),
                                           std::make_tuple(Vector2{ 1.0f, 1.0f }, 1.0f, Vector2{ 1.0f, 1.0f })));

TEST(Vector2, DevideByZeroExpectionDivide) {
    auto constexpr vec_c = Vector2{ 1.0f, 1.0f };
    auto vec_m           = Vector2{ 1.0f, 1.0f };
    auto constexpr f     = 0.0f;

    try {
        [[maybe_unused]] auto const result = vec_c / f;
        GTEST_FAIL() << "DevideByZero not thrown while operator/";
    } catch (uil::DivideByZero const& e) {
        EXPECT_STREQ(e.what(), "Devide by zero while deviding a vector by a float");
    }

    try {
        vec_m /= f;
        GTEST_FAIL() << "DevideByZero not thrown while operator/=";
    } catch (uil::DivideByZero const& e) {
        EXPECT_STREQ(e.what(), "Devide by zero while deviding a vector by a float");
    }
}

class Vector2ToAbsoluteFixtures : public testing::TestWithParam<std::tuple<Vector2, cpt::Vec2_i, Vector2>> { };

TEST_P(Vector2ToAbsoluteFixtures, Succsess) {
    auto const relative   = std::get<0>(GetParam());
    auto const resolution = std::get<1>(GetParam());
    auto const expected   = std::get<2>(GetParam());

    auto const result = uil::to_absolute(relative, resolution);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(
        VECTOR2,
        Vector2ToAbsoluteFixtures,
        ::testing::Values(
                std::make_tuple(Vector2{ 0.25f, 0.25f }, cpt::Vec2_i{ 1000, 1000 }, Vector2{ 250.0f, 250.0f }),
                std::make_tuple(Vector2{ 0.1f, 0.2f }, cpt::Vec2_i{ 1000, 500 }, Vector2{ 100.0f, 100.0f })));


class Vector2ToRealtiveFixtures : public testing::TestWithParam<std::tuple<Vector2, cpt::Vec2_i, Vector2>> { };

TEST_P(Vector2ToRealtiveFixtures, Succsess) {
    auto const absolute   = std::get<0>(GetParam());
    auto const resolution = std::get<1>(GetParam());
    auto const expected   = std::get<2>(GetParam());

    auto const result = uil::to_relative(absolute, resolution);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(
        VECTOR2,
        Vector2ToRealtiveFixtures,
        ::testing::Values(
                std::make_tuple(Vector2{ 250.0f, 250.0f }, cpt::Vec2_i{ 1000, 1000 }, Vector2{ 0.25f, 0.25f }),
                std::make_tuple(Vector2{ 100.0f, 100.0f }, cpt::Vec2_i{ 1000, 500 }, Vector2{ 0.1f, 0.2f })));
