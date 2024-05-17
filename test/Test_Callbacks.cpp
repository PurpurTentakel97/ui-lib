//
// Purpur Tentakel
// 17.05.24
//

#include <gtest/gtest.h>
#include <uil/Callback.hpp>

TEST(Callbacks, CallsCallbackOnce) {
    auto callbacks = uil::Callback();
    auto counter   = 0;
    callbacks += [&counter]() { ++counter; };

    EXPECT_EQ(counter, 0);
    callbacks.invoke();
    EXPECT_EQ(counter, 1);
    EXPECT_EQ(callbacks.size(), 1);
}

TEST(Callbacks, CallsCallbackClear) {
    auto callbacks = uil::Callback();
    auto counter   = 0;
    callbacks += [&counter]() { ++counter; };

    callbacks.clear();
    callbacks.invoke();
    EXPECT_EQ(counter, 0);
    EXPECT_TRUE(callbacks.is_empty());
}

TEST(Callbacks, AddInvalidFunction) {
    auto callbacks = uil::Callback();
    std::function<void()> func;

    try {
        callbacks += func;
        GTEST_FAIL() << "uil::CallbackException not thrown";
    }
    catch(uil::CallbackException const& e) {
        EXPECT_STREQ(e.what(), "register of bad callback function");
    }
}
