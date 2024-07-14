//
// Purpur Tentakel
// 06.07.24
//

#include <gtest/gtest.h>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

class AlignmentFicturesVertical
    : public testing::TestWithParam<std::tuple<Rectangle, uil::VerticalAlignment, Rectangle>> { };


TEST_P(AlignmentFicturesVertical, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    EXPECT_FLOAT_EQ(unaligned.x, aligned.x);

    auto const result = uil::vertical_aligned_position(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.x, unaligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);

    EXPECT_FLOAT_EQ(result.width, aligned.height);
    EXPECT_FLOAT_EQ(result.width, unaligned.height);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}


INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentFicturesVertical,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Top,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.5f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Mid,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.75f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Bottom,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f })));


TEST(Alignment, VerticalException) {
    auto constexpr value = static_cast<uil::VerticalAlignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::vertical_aligned_position(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "expection uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid vertical alignmend enum while aligning rectanlge verticaly");
    }
}

class AlignmentFicturesVerticalReversed
    : public testing::TestWithParam<std::tuple<Rectangle, uil::VerticalAlignment, Rectangle>> { };

TEST_P(AlignmentFicturesVerticalReversed, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    EXPECT_FLOAT_EQ(unaligned.x, aligned.x);

    auto const result = uil::vertical_aligned_position_reversed(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.x, unaligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);

    EXPECT_FLOAT_EQ(result.width, aligned.height);
    EXPECT_FLOAT_EQ(result.width, unaligned.height);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentFicturesVerticalReversed,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Top,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Mid,
                                                           Rectangle{ 0.25f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Bottom,
                                                           Rectangle{ 0.25f, 0.75f, 0.5f, 0.5f })));

TEST(Alignment, VerticalExceptionReversed) {
    auto constexpr value = static_cast<uil::VerticalAlignment>(100);

    try {
        [[maybe_unused]] auto const result
                = uil::vertical_aligned_position_reversed(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "expection uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid vertical alignmend enum while reversed aligning rectanlge verticaly");
    }
}

class DoubleVerticalAlignmentFixtures : public testing::TestWithParam<uil::VerticalAlignment> { };

TEST_P(DoubleVerticalAlignmentFixtures, DobleHorizontalCovert) {
    auto const alignment     = GetParam();
    auto constexpr unaligned = Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f };

    auto const temp   = uil::vertical_aligned_position(unaligned, alignment);
    auto const result = uil::vertical_aligned_position_reversed(temp, alignment);

    EXPECT_FLOAT_EQ(result.x, unaligned.x);
    EXPECT_FLOAT_EQ(result.y, unaligned.y);
    EXPECT_FLOAT_EQ(result.width, unaligned.width);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         DoubleVerticalAlignmentFixtures,
                         testing::Values(uil::VerticalAlignment::Top,
                                         uil::VerticalAlignment::Mid,
                                         uil::VerticalAlignment::Bottom));

class VerticalAlignmentFicturesVertical
    : public testing::TestWithParam<std::tuple<Vector2, Vector2, uil::VerticalAlignment, Vector2>> { };

TEST_P(VerticalAlignmentFicturesVertical, Succsess) {
    auto const pos       = std::get<0>(GetParam());
    auto const size      = std::get<1>(GetParam());
    auto const alignment = std::get<2>(GetParam());
    auto const expected  = std::get<3>(GetParam());

    auto const result = uil::vertical_aligned_position(pos, size, alignment);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
    EXPECT_FLOAT_EQ(pos.x, result.x);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VerticalAlignmentFicturesVertical,
                         ::testing::Values(std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Top,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.5f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Mid,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.75f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Bottom,
                                                           Vector2{ 0.25f, 0.25f })));


class VectorAlignmentFicturesVerticalReversed
    : public testing::TestWithParam<std::tuple<Vector2, Vector2, uil::VerticalAlignment, Vector2>> { };

TEST_P(VectorAlignmentFicturesVerticalReversed, Success) {
    auto const pos       = std::get<0>(GetParam());
    auto const size      = std::get<1>(GetParam());
    auto const alignment = std::get<2>(GetParam());
    auto const expected  = std::get<3>(GetParam());

    auto const result = uil::vertical_aligned_position_reversed(pos, size, alignment);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
    EXPECT_FLOAT_EQ(pos.x, result.x);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VectorAlignmentFicturesVerticalReversed,
                         ::testing::Values(std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Top,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Mid,
                                                           Vector2{ 0.25f, 0.5f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::VerticalAlignment::Bottom,
                                                           Vector2{ 0.25f, 0.75f })));


class VectorDoubleVerticalAlignmentFixtures : public testing::TestWithParam<uil::VerticalAlignment> { };

TEST_P(VectorDoubleVerticalAlignmentFixtures, Succsess) {
    auto const alignment = GetParam();

    auto constexpr pos  = Vector2{ 0.25f, 0.25f };
    auto constexpr size = Vector2{ 0.5f, 0.5f };

    auto const temp   = uil::vertical_aligned_position(pos, size, alignment);
    auto const result = uil::vertical_aligned_position_reversed(temp, size, alignment);

    EXPECT_FLOAT_EQ(pos.x, result.x);
    EXPECT_FLOAT_EQ(pos.y, result.y);
    EXPECT_FLOAT_EQ(pos.x, temp.x);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VectorDoubleVerticalAlignmentFixtures,
                         testing::Values(uil::VerticalAlignment::Top,
                                         uil::VerticalAlignment::Mid,
                                         uil::VerticalAlignment::Bottom));
