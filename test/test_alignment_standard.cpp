//
// Purpur Tentakel
// 23.05.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>


class AlignmentFictures : public testing::TestWithParam<std::tuple<Rectangle, uil::Alignment, Rectangle>> { };

TEST_P(AlignmentFictures, Sucsess) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    auto const result = uil::aligned_position(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);

    EXPECT_FLOAT_EQ(result.width, aligned.width);
    EXPECT_FLOAT_EQ(result.width, unaligned.width);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentFictures,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.5f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.75f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.75f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.5f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.75f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f })));

TEST(Alignment, Exception) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::aligned_position(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum while aligning rectangle"); }
}

class AlignmentRevesedFixuteres : public testing::TestWithParam<std::tuple<Rectangle, uil::Alignment, Rectangle>> { };

TEST_P(AlignmentRevesedFixuteres, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const alignment = std::get<1>(GetParam());
    auto const aligned   = std::get<2>(GetParam());

    auto const result = uil::aligned_position_reversed(unaligned, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);

    EXPECT_FLOAT_EQ(result.height, aligned.height);
    EXPECT_FLOAT_EQ(result.height, aligned.height);

    EXPECT_FLOAT_EQ(result.width, aligned.width);
    EXPECT_FLOAT_EQ(result.width, aligned.width);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentRevesedFixuteres,
                         ::testing::Values(std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           Rectangle{ 0.5f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           Rectangle{ 0.75f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           Rectangle{ 0.25f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           Rectangle{ 0.75f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           Rectangle{ 0.25f, 0.75f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           Rectangle{ 0.5f, 0.75f, 0.5f, 0.5f }),
                                           std::make_tuple(Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           Rectangle{ 0.75f, 0.75f, 0.5f, 0.5f })));

TEST(Alignment, ReversedException) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::aligned_position_reversed(Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum while reversed aligning rectangle"); }
}

class DoubleAlignmentFixtures : public testing::TestWithParam<uil::Alignment> { };

TEST_P(DoubleAlignmentFixtures, DoubleConvert) {
    auto const alignment     = GetParam();
    auto constexpr unaligned = Rectangle{ 0.25f, 0.25f, 0.5f, 0.5f };

    auto const temp   = uil::aligned_position(unaligned, alignment);
    auto const result = uil::aligned_position_reversed(temp, alignment);

    EXPECT_FLOAT_EQ(result.x, unaligned.x);
    EXPECT_FLOAT_EQ(result.y, unaligned.y);
    EXPECT_FLOAT_EQ(result.width, unaligned.width);
    EXPECT_FLOAT_EQ(result.height, unaligned.height);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         DoubleAlignmentFixtures,
                         ::testing::Values(uil::Alignment::TopLeft,
                                           uil::Alignment::TopMid,
                                           uil::Alignment::TopRight,
                                           uil::Alignment::MidLeft,
                                           uil::Alignment::MidMid,
                                           uil::Alignment::MidRight,
                                           uil::Alignment::BottomLeft,
                                           uil::Alignment::BottomMid,
                                           uil::Alignment::BottomRight));
