//
// Purpur Tentakel
// 06.07.24
//

#include <iostream>
#include <uil/test_scene.hpp>
#include <uil/text.hpp>

namespace uil {
    void TestScene::start_callback(UIElement const& text) const {
        std::cout << "started moving - moving: " << text.has_started_moving() << '\n';
    }

    void TestScene::stop_callback(UIElement const& text) const {
        std::cout << "stopped moving - stopped: " << text.has_stopped_moving() << '\n';
    }

    void TestScene::arrived_callback(UIElement const& text) const {
        std::cout << "arrived - stopped: " << text.has_stopped_moving() << '\n';
    }

    TestScene::TestScene(cpt::Vec2_i const resolution) {
        m_text = &emplace_element<Text>(
                Rectangle{ 0.25f, 0.5f, 0.25f, 0.25f }, Alignment::MidMid, resolution, 0.1f);
        m_text->set_color(PURPLE);
        m_text->set_spacing(3.0f);
        m_text->set_text("Bester Text");
        m_text->set_render_collider(true);
        m_text->on_movement_start += [this](UIElement const& text) { this->start_callback(text); };
        m_text->on_movement_stop += [this](UIElement const& text) { this->stop_callback(text); };
        m_text->on_arrived += [this](UIElement const& text) { this->arrived_callback(text); };
    }

    bool TestScene::check(Vector2 const& mousePosition) const {
        auto const result = Scene::check(mousePosition);

        static auto start = GetTime();
        static auto index = 0;
        auto const inc    = [&i = index]() {
            ++i;
            start = GetTime();
            if (index > 7) {
                index = 0;
            }
        };

        if (not m_text->is_moving()) {
            auto const stop = GetTime();
            std::cout << "time: " << stop - start << '\n';
            switch (index) {
                case 0: m_text->move_to_slow_to_fast(m_bottom_left, 0.5f); break;
                case 1: m_text->move_to_fast_to_slow(m_bottom_right, 0.2f); break;
                case 2: m_text->move_to_linear_speed(m_top_right, 0.5f); break;
                case 3: m_text->move_to_linear_time(m_top_left, 1.0f); break;
                case 4: m_text->move_to_slow_to_fast(m_bottom_right, 2.0f); break;
                case 5: m_text->move_to_fast_to_slow(m_top_right, 5.0); break;
                case 6: m_text->move_to_linear_speed(m_bottom_left, 10.0f); break;
                case 7: m_text->move_to_linear_time(m_top_left, 15.0f); break;
            }
            inc();
        }


        return result;
    }

    bool TestScene::render(Font const* font) const {
        auto const result = Scene::render(font);

        // clang-format off
        DrawCircle(
            static_cast<int>(m_top_left.x * 1920.0f),
            static_cast<int>(m_top_left.y * 1080.0f),
            2.0f,
            WHITE
            );
        DrawCircle(
            static_cast<int>(m_bottom_left.x * 1920.0f),
            static_cast<int>(m_bottom_left.y * 1080.0f),
            2.0f,
                WHITE
            );
        DrawCircle(
            static_cast<int>(m_bottom_right.x * 1920.0f),
            static_cast<int>(m_bottom_right.y * 1080.0f),
            2.0f,
            WHITE
            );
        DrawCircle(
            static_cast<int>(m_top_right.x * 1920.0f),
            static_cast<int>(m_top_right.y * 1080.0f),
            2.0f,
            WHITE
            );
        // clang-format on

        return result;
    }
} // namespace uil
