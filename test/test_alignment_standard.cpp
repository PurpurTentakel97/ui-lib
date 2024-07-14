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
    EXPECT_FLOAT_EQ(result.height, unaligned.height);

    EXPECT_FLOAT_EQ(result.width, aligned.width);
    EXPECT_FLOAT_EQ(result.width, unaligned.width);
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
    } catch (uil::BadAlignment const& e) {
        EXPECT_STREQ(e.what(), "invalid alignment enum while reversed aligning rectangle");
    }
}

class DoubleAlignmentFixtures : public testing::TestWithParam<uil::Alignment> { };

TEST_P(DoubleAlignmentFixtures, Succsess) {
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


// clang-format off
class VectorAlignmentFixtures : public testing::TestWithParam<std::tuple<Vector2, Vector2, uil::Alignment, Vector2>> { };
// clang-format on

TEST_P(VectorAlignmentFixtures, Succsess) {
    auto const pos          = std::get<0>(GetParam());
    auto const size         = std::get<1>(GetParam());
    auto const alignment    = std::get<2>(GetParam());
    auto const expected_pos = std::get<3>(GetParam());

    auto const result = uil::aligned_position(pos, size, alignment);

    EXPECT_FLOAT_EQ(expected_pos.x, result.x);
    EXPECT_FLOAT_EQ(expected_pos.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VectorAlignmentFixtures,
                         ::testing::Values(std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.5f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.75f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.5f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.5f, 0.5f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.75f, 0.5f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.75f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.5f, 0.75f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.75f, 0.75f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           Vector2{ 0.25f, 0.25f })));


class VectorAlignmentReversedFictures
    : public testing::TestWithParam<std::tuple<Vector2, Vector2, uil::Alignment, Vector2>> { };

TEST_P(VectorAlignmentReversedFictures, Succsess) {
    auto const pos       = std::get<0>(GetParam());
    auto const size      = std::get<1>(GetParam());
    auto const alignment = std::get<2>(GetParam());
    auto const expected  = std::get<3>(GetParam());

    auto const result = uil::aligned_position_reversed(pos, size, alignment);

    EXPECT_FLOAT_EQ(expected.x, result.x);
    EXPECT_FLOAT_EQ(expected.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VectorAlignmentReversedFictures,
                         ::testing::Values(std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopLeft,
                                                           Vector2{ 0.25f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopMid,
                                                           Vector2{ 0.5f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::TopRight,
                                                           Vector2{ 0.75f, 0.25f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidLeft,
                                                           Vector2{ 0.25f, 0.5f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidMid,
                                                           Vector2{ 0.5f, 0.5f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::MidRight,
                                                           Vector2{ 0.75f, 0.5f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomLeft,
                                                           Vector2{ 0.25f, 0.75f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomMid,
                                                           Vector2{ 0.5f, 0.75f }),
                                           std::make_tuple(Vector2{ 0.25f, 0.25f },
                                                           Vector2{ 0.5f, 0.5f },
                                                           uil::Alignment::BottomRight,
                                                           Vector2{ 0.75f, 0.75f })));


class VectorDoubleAlignmendFixtures : public testing::TestWithParam<uil::Alignment> { };

TEST_P(VectorDoubleAlignmendFixtures, Succsess) {
    auto const alignment = GetParam();
    auto constexpr pos   = Vector2{ 0.25f, 0.25f };
    auto constexpr size  = Vector2{ 0.5f, 0.5f };

    auto const temp   = uil::aligned_position(pos, size, alignment);
    auto const result = uil::aligned_position_reversed(temp, size, alignment);

    EXPECT_FLOAT_EQ(pos.x, result.x);
    EXPECT_FLOAT_EQ(pos.y, result.y);
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         VectorDoubleAlignmendFixtures,
                         ::testing::Values(uil::Alignment::TopLeft,
                                           uil::Alignment::TopMid,
                                           uil::Alignment::TopRight,
                                           uil::Alignment::MidLeft,
                                           uil::Alignment::MidMid,
                                           uil::Alignment::MidRight,
                                           uil::Alignment::BottomLeft,
                                           uil::Alignment::BottomMid,
                                           uil::Alignment::BottomRight));
