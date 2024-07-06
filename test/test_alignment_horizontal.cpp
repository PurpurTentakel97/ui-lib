//
// Purpur Tentakel
// 06.07.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

class AlignmentHorizontalFictures
    : public testing::TestWithParam<std::tuple<Rectangle, uil::HorizontalAlignment, Rectangle>> { };


TEST_P(AlignmentHorizontalFictures, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    EXPECT_FLOAT_EQ(unaligned.y, aligned.y);

    auto const result = uil::horizontal_aligned_position(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);
    EXPECT_FLOAT_EQ(result.y, unaligned.y);

    EXPECT_FLOAT_EQ(result.width, aligned.height);
    EXPECT_FLOAT_EQ(result.width, unaligned.height);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}


INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentHorizontalFictures,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Left,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.5f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Mid,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.75f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Right,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f })));


TEST(Alignment, HorizontalException) {
    auto constexpr value = static_cast<uil::HorizontalAlignment>(100);

    try {
        [[maybe_unused]] auto const result =
                uil::horizontal_aligned_position(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "expection uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid horizontal alignmend enum while aligning rectanlge horizonalty");
    }
}

class AlignmentHorizontalReversedFictures
    : public testing::TestWithParam<std::tuple<Rectangle, uil::HorizontalAlignment, Rectangle>> { };

TEST_P(AlignmentHorizontalReversedFictures, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    EXPECT_FLOAT_EQ(unaligned.y, aligned.y);

    auto const result = uil::horizontal_aligned_position_reversed(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);
    EXPECT_FLOAT_EQ(result.y, unaligned.y);

    EXPECT_FLOAT_EQ(result.width, aligned.height);
    EXPECT_FLOAT_EQ(result.width, unaligned.height);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentHorizontalReversedFictures,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Left,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Mid,
                                                           Rectangle{ 0.5f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::HorizontalAlignment::Right,
                                                           Rectangle{ 0.75f, 0.25f, 0.5f, 0.5f })));

TEST(Alignment, HorizontalExceptionReversed) {
    auto constexpr value = static_cast<uil::HorizontalAlignment>(100);

    try {
        [[maybe_unused]] auto const result =
                uil::horizontal_aligned_position_reversed(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "expection uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid horizontal alignmend enum while reversed aligning rectanlge horizonalty");
    }
}

class DoubleHorizontalAlignmentFixtures : public testing::TestWithParam<uil::HorizontalAlignment> { };

TEST_P(DoubleHorizontalAlignmentFixtures, DobleHorizontalCovert) {
    auto const alignment     = GetParam();
    auto constexpr unaligned = Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f };

    auto const temp   = uil::horizontal_aligned_position(unaligned, alignment);
    auto const result = uil::horizontal_aligned_position_reversed(temp, alignment);

    EXPECT_FLOAT_EQ(result.x, unaligned.x);
    EXPECT_FLOAT_EQ(result.y, unaligned.y);
    EXPECT_FLOAT_EQ(result.width, unaligned.width);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         DoubleHorizontalAlignmentFixtures,
                         testing::Values(uil::HorizontalAlignment::Left,
                                         uil::HorizontalAlignment::Mid,
                                         uil::HorizontalAlignment::Right));
