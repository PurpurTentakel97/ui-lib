//
// Purpur Tentakel
// 23.05.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

class AlignmentFictures
    : public testing::TestWithParam<std::tuple<cpt::Vec2f, cpt::Vec2f, uil::Alignment, cpt::Vec2f>> { };

TEST_P(AlignmentFictures, Sucsess) {
    auto const unaligned = std::get<0>(GetParam());
    auto const size      = std::get<1>(GetParam());
    auto const alignment = std::get<2>(GetParam());
    auto const aligned   = std::get<3>(GetParam());

    auto const result = uil::aligned_position(unaligned, size, alignment);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentFictures,
                         ::testing::Values(std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.5f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.75f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.5f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.5f, 0.5f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.75f, 0.5f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.75f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.5f, 0.75f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.75f, 0.75f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           cpt::Vec2f{ 0.25f, 0.25f })));

TEST(Alignment, PositionException) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result =
                uil::aligned_position(cpt::Vec2f{ 0.0f, 0.0f }, cpt::Vec2f{ 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum"); }
}

class AlignmentRevesedFixuteres
    : public testing::TestWithParam<std::tuple<cpt::Vec2f, cpt::Vec2f, uil::Alignment, cpt::Vec2f>> { };

TEST_P(AlignmentRevesedFixuteres, Success) {
    auto const unaligned = std::get<0>(GetParam());
    auto const size      = std::get<1>(GetParam());
    auto const alignemnt = std::get<2>(GetParam());
    auto const aligned   = std::get<3>(GetParam());

    auto const result = uil::aligned_position_reversed(unaligned, size, alignemnt);
    EXPECT_FLOAT_EQ(result.x, aligned.x);
    EXPECT_FLOAT_EQ(result.y, aligned.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         AlignmentRevesedFixuteres,
                         ::testing::Values(std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           cpt::Vec2f{ 0.25f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           cpt::Vec2f{ 0.5f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           cpt::Vec2f{ 0.75f, 0.25f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           cpt::Vec2f{ 0.25f, 0.5f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           cpt::Vec2f{ 0.5f, 0.5f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           cpt::Vec2f{ 0.75f, 0.5f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           cpt::Vec2f{ 0.25f, 0.75f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           cpt::Vec2f{ 0.5f, 0.75f }),
                                           std::make_tuple(cpt::Vec2f{ 0.25f, 0.25f },
                                                           cpt::Vec2f{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           cpt::Vec2f{ 0.75f, 0.75f })));

TEST(Alignment, PositionReversedException) {
    auto constexpr value = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result =
                uil::aligned_position_reversed(cpt::Vec2f{ 0.0f, 0.0f }, cpt::Vec2f{ 0.0f, 0.0f }, value);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) { EXPECT_STREQ(e.what(), "invalid alignment enum"); }
}

class DoubleAlignmentFixtures : public testing::TestWithParam<uil::Alignment> { };

TEST_P(DoubleAlignmentFixtures, DoubleConvert) {
    auto const alignement   = GetParam();
    auto constexpr position = cpt::Vec2f{ 0.25f, 0.25f };
    auto constexpr size     = cpt::Vec2f{ 0.5f, 0.5f };

    auto const temp   = uil::aligned_position(position, size, alignement);
    auto const result = uil::aligned_position_reversed(temp, size, alignement);

    EXPECT_FLOAT_EQ(result.x, position.x);
    EXPECT_FLOAT_EQ(result.y, position.y);
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
