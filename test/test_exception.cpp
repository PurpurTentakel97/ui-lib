//
// Purpur Tentakel
// 27.05.24
//

#include <gtest/gtest.h>
#include <uil/exception.hpp>

TEST(Exception, CallbackException) {
    try {
        throw uil::CallbackException("some callback fail");
    } catch (std::runtime_error const& e) {
        EXPECT_STREQ(e.what(), "some callback fail");
    } catch ([[maybe_unused]] std::exception const& e) {
        GTEST_FAIL() << "uil::CallbackException is no std::runtime_error";
    }
}

TEST(Exception, DivideByZero) {
    try {
        throw uil::DivideByZero("some divide by zero fail");
    } catch (std::runtime_error const& e) {
        EXPECT_STREQ(e.what(), "some divide by zero fail");
    } catch ([[maybe_unused]] std::exception const& e) {
        GTEST_FAIL() << "uil::DivideByZero is no std::runtime_error";
    }
}

TEST(Exception, BadResolution) {
    try {
        throw uil::BadResolution("some resolution fail");
    } catch (std::logic_error const& e) {
        EXPECT_STREQ(e.what(), "some resolution fail");
    } catch ([[maybe_unused]] std::exception const& e) {
        GTEST_FAIL() << "uil::CallbackException is no std::logic_error";
    }
}

TEST(Exception, BadAlignment) {
    try {
        throw uil::BadAlignment("some alignment fail");
    } catch (std::logic_error const& e) {
        EXPECT_STREQ(e.what(), "some alignment fail");
    } catch ([[maybe_unused]] std::exception const& e) {
        GTEST_FAIL() << "uil::CallbackException is no std::logic_error";
    }
}
