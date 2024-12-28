//
// Purpur Tentakel
// 06.07.24
//

#include <gtest/gtest.h>
#include <tuple>
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

class ToHorizontalAlignmentFixtures
    : public testing::TestWithParam<std::tuple<uil::Alignment, uil::HorizontalAlignment>> { };

TEST_P(ToHorizontalAlignmentFixtures, Succses) {
    auto const alignment            = std::get<0>(GetParam());
    auto const horizontal_alignment = std::get<1>(GetParam());

    auto const result = uil::to_horizontal_alignment(alignment);

    EXPECT_EQ(result, horizontal_alignment);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         ToHorizontalAlignmentFixtures,
                         ::testing::Values(std::make_tuple(uil::Alignment::TopLeft, uil::HorizontalAlignment::Left),
                                           std::make_tuple(uil::Alignment::TopMid, uil::HorizontalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::TopRight, uil::HorizontalAlignment::Right),
                                           std::make_tuple(uil::Alignment::MidLeft, uil::HorizontalAlignment::Left),
                                           std::make_tuple(uil::Alignment::MidMid, uil::HorizontalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::MidRight, uil::HorizontalAlignment::Right),
                                           std::make_tuple(uil::Alignment::BottomLeft, uil::HorizontalAlignment::Left),
                                           std::make_tuple(uil::Alignment::BottomMid, uil::HorizontalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::BottomRight,
                                                           uil::HorizontalAlignment::Right)));

TEST(Alignment, ToHorizontalException) {
    auto constexpr alignment = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::to_horizontal_alignment(alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(),
                     "invalid alignment enum while converting an alignment enum to a horizontal alignment enum");
    }
}


class ToVerticalAlignmentFixtures : public testing::TestWithParam<std::tuple<uil::Alignment, uil::VerticalAlignment>> {
};

TEST_P(ToVerticalAlignmentFixtures, Sucsses) {
    auto const alignment          = std::get<0>(GetParam());
    auto const vertical_alignment = std::get<1>(GetParam());

    auto const result = uil::to_vertical_alignment(alignment);

    EXPECT_EQ(result, vertical_alignment);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         ToVerticalAlignmentFixtures,
                         ::testing::Values(std::make_tuple(uil::Alignment::TopLeft, uil::VerticalAlignment::Top),
                                           std::make_tuple(uil::Alignment::TopMid, uil::VerticalAlignment::Top),
                                           std::make_tuple(uil::Alignment::TopRight, uil::VerticalAlignment::Top),
                                           std::make_tuple(uil::Alignment::MidLeft, uil::VerticalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::MidMid, uil::VerticalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::MidRight, uil::VerticalAlignment::Mid),
                                           std::make_tuple(uil::Alignment::BottomLeft, uil::VerticalAlignment::Bottom),
                                           std::make_tuple(uil::Alignment::BottomMid, uil::VerticalAlignment::Bottom),
                                           std::make_tuple(uil::Alignment::BottomRight,
                                                           uil::VerticalAlignment::Bottom)));

TEST(Alignment, ToVerticalExpection) {
    auto constexpr alignment = static_cast<uil::Alignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::to_vertical_alignment(alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid alignment enum while converting an alignment enum to a vertical alignment enum");
    }
}


class ToAlignmentFictures
    : public testing::TestWithParam<std::tuple<uil::VerticalAlignment, uil::HorizontalAlignment, uil::Alignment>> { };

TEST_P(ToAlignmentFictures, Sucsess) {
    auto const vertical_alignment   = std::get<0>(GetParam());
    auto const horizontal_alignment = std::get<1>(GetParam());
    auto const alignment            = std::get<2>(GetParam());

    auto const result = uil::to_alignment(vertical_alignment, horizontal_alignment);

    EXPECT_EQ(alignment, result);
}

INSTANTIATE_TEST_SUITE_P(
        ALIGNMENT,
        ToAlignmentFictures,
        ::testing::Values(
                // clang-format off
                std::make_tuple(uil::VerticalAlignment::Top,    uil::HorizontalAlignment::Left,  uil::Alignment::TopLeft     ),
                std::make_tuple(uil::VerticalAlignment::Top,    uil::HorizontalAlignment::Mid,   uil::Alignment::TopMid      ),
                std::make_tuple(uil::VerticalAlignment::Top,    uil::HorizontalAlignment::Right, uil::Alignment::TopRight    ),
                std::make_tuple(uil::VerticalAlignment::Mid,    uil::HorizontalAlignment::Left,  uil::Alignment::MidLeft     ),
                std::make_tuple(uil::VerticalAlignment::Mid,    uil::HorizontalAlignment::Mid,   uil::Alignment::MidMid      ),
                std::make_tuple(uil::VerticalAlignment::Mid,    uil::HorizontalAlignment::Right, uil::Alignment::MidRight    ),
                std::make_tuple(uil::VerticalAlignment::Bottom, uil::HorizontalAlignment::Left,  uil::Alignment::BottomLeft  ),
                std::make_tuple(uil::VerticalAlignment::Bottom, uil::HorizontalAlignment::Mid,   uil::Alignment::BottomMid   ),
                std::make_tuple(uil::VerticalAlignment::Bottom, uil::HorizontalAlignment::Right, uil::Alignment::BottomRight )));
// clang-format on


TEST(Alignment, ToAlignmentExceptionVertical) {
    auto constexpr vertical_alignment   = static_cast<uil::VerticalAlignment>(100);
    auto constexpr horizontal_alignment = uil::HorizontalAlignment::Left;

    try {
        [[maybe_unused]] auto const result = uil::to_alignment(vertical_alignment, horizontal_alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid vertical alignment enum while converting to an alignment enum");
    }
}

TEST(Alignment, ToAlignmentExceptionHorizontalTop) {
    auto constexpr vertical_alignment   = uil::VerticalAlignment::Top;
    auto constexpr horizontal_alignment = static_cast<uil::HorizontalAlignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::to_alignment(vertical_alignment, horizontal_alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(),
                     "invalid horizontal alignment enum while converting to an alignment enum with vertical top enum");
    }
}

TEST(Alignment, ToAlignmentExceptionHorizontalMid) {
    auto constexpr vertical_alignment   = uil::VerticalAlignment::Mid;
    auto constexpr horizontal_alignment = static_cast<uil::HorizontalAlignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::to_alignment(vertical_alignment, horizontal_alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(),
                     "invalid horizontal alignment enum while converting to an alignment enum with vertical mid enum");
    }
}

TEST(Alignment, ToAlignmentExceptionHorizontalBottom) {
    auto constexpr vertical_alignment   = uil::VerticalAlignment::Bottom;
    auto constexpr horizontal_alignment = static_cast<uil::HorizontalAlignment>(100);

    try {
        [[maybe_unused]] auto const result = uil::to_alignment(vertical_alignment, horizontal_alignment);
        GTEST_FAIL() << "exception uil::BadAlignment not thrown";
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(
                e.what(),
                "invalid horizontal alignment enum while converting to an alignment enum with vertical bottom enum");
    }
}
