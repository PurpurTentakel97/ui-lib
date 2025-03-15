//
// Purpur Tentakel
// 14.03.25
//

#include <cpt/vec2.hpp>
#include <future>
#include <gtest/gtest.h>
#include <raylib.h>
#include <thread>
#include <uil/alignment.hpp>
#include <uil/context.hpp>
#include <uil/elements/text.hpp>
#include <uil/scene_manager.hpp>

class TextInputBreaking : public testing::TestWithParam<std::string> { };

TEST_P(TextInputBreaking, Success) {
    auto const input = GetParam();
    std::promise<void> promise;
    std::future<void> const future = promise.get_future();

    std::thread worker([&]() {
        auto const font = LoadFont("assets/font.ttf");

        auto text = uil::Text{
            cpt::Vec2_i{ 600, 800 },
            Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f },
            uil::Alignment::MidMid
        };
        auto manager = uil::SceneManager{
            cpt::Vec2_i{ 800, 600 }
        };
        [[maybe_unused]] auto const result = text.handle_input(uil::Context{
                Vector2{ 100, 100 },
                &font, cpt::Vec2_i{ 800, 600 },
                0.5f, manager
        });
        text.set_breaking(true);
        text.set_text(input);
        text.update_text();
        promise.set_value();
    });

    auto const status = future.wait_for(std::chrono::seconds(2));
    if (status == std::future_status::timeout) {
        worker.detach();
        GTEST_FAIL() << "timed out | possible infinite loop | '" << input << "'";
    }

    worker.join();
}

INSTANTIATE_TEST_SUITE_P(ALIGNMENT,
                         TextInputBreaking,
                         ::testing::Values("",
                                           " ",
                                           "\n",
                                           "    aklsdfalksdjhfadf",
                                           "kjahdfkljhadsf    ",
                                           "kljadhsfkljahdsf\nkjlahdsflkjahsdf"));
