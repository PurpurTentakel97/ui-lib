//
// Purpur Tentakel
// 23.05.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

class AlignmentFictures : public testing::TestWithParam<std::tuple<cpt::Rect_f, uil::Alignment, cpt::Rect_f>> { };

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
                         ::testing::Values(std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.5f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.75f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.5f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.75f, 0.5f, 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.5f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.75f, 0.75f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f })));

TEST(Alignment, PositionException) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::aligned_position(cpt::Rect_f{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum"); }
}

class AlignmentRevesedFixuteres : public testing::TestWithParam<std::tuple<cpt::Rect_f, uil::Alignment, cpt::Rect_f>> { };

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
                         ::testing::Values(std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           cpt::Rect_f{ 0.5f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           cpt::Rect_f{ 0.75f, 0.25f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           cpt::Rect_f{ 0.25f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           cpt::Rect_f{ 0.5f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           cpt::Rect_f{ 0.75f, 0.5f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           cpt::Rect_f{ 0.25f, 0.75f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           cpt::Rect_f{ 0.5f, 0.75f, 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           cpt::Rect_f{ 0.75f, 0.75f, 0.5f, 0.5f })));

TEST(Alignment, PositionReversedException) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::aligned_position_reversed(cpt::Rect_f{ 0.0f, 0.0f, 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum"); }
}

class DoubleAlignmentFixtures : public testing::TestWithParam<uil::Alignment> { };

TEST_P(DoubleAlignmentFixtures, DoubleConvert) {
    auto const alignment    = GetParam();
    auto constexpr unaligned = cpt::Rect_f{ 0.25f, 0.25f, 0.5f, 0.5f };

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
