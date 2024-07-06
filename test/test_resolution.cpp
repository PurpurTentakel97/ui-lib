//
// Purpur Tentakel
// 28.05.24
//

#include <gtest/gtest.h>
#include <uil/exception.hpp>
#include <uil/resolution.hpp>

TEST(Resolution, VecThrow) {
    auto constexpr res = static_cast<uil::Resolution>(300);

    try {
        [[maybe_unused]] auto const result = uil::vec_from_resolution(res);
        GTEST_FAIL() << "exception uil::BadResolution not thrown";
    } catch (uil::BadResolution const& e) { EXPECT_STREQ(e.what(), "unexpected resolution in vec switch case"); }
}

TEST(Resolution, StrThrow) {
    auto constexpr res = static_cast<uil::Resolution>(200);

    try {
        [[maybe_unused]] auto const result = uil::str_from_resolution(res);
        GTEST_FAIL() << "exception uil::BadResolution not thrown";
    } catch (uil::BadResolution const& e) { EXPECT_STREQ(e.what(), "unexpected resolution in string switch case"); }
}

TEST(Resolution, AllStringCount) {
    auto const string_vec = uil::all_string_from_resolution();
    EXPECT_EQ(string_vec.size(), 28);
}
