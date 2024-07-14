//
// Purpur Tentakel
// 06.07.24
//

#include <iostream>
#include <uil/test_scene.hpp>
#include <uil/text.hpp>

namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution) {
        m_text = &emplace_element<Text>(Rectangle{ 0.25f, 0.5f, 0.25f, 0.25f }, Alignment::MidMid, resolution, 0.1f);
        m_text->set_color(PURPLE);
        m_text->set_spacing(3.0f);
        m_text->set_text("Bester Text");
        m_text->set_render_collider(true);
    }
    bool TestScene::check(Vector2 const& mousePosition) const {
        auto const result = Scene::check(mousePosition);

        auto constexpr speed = 0.2f;
        static auto index    = 0;
        auto const inc       = [&i = index]() {
            ++i;
            if (index > 7) {
                index = 0;
            }
        };

        if (not m_text->is_moving()) {
            std::cout << index << '\n';
            switch (index) {
                case 0: m_text->move_to_linear(m_bottom_left, speed); break;
                case 1: m_text->move_to_linear(m_bottom_right, speed); break;
                case 2: m_text->move_to_linear(m_top_right, speed); break;
                case 3: m_text->move_to_linear(m_top_left, speed); break;
                case 4: m_text->move_to_linear(m_bottom_right, speed); break;
                case 5: m_text->move_to_linear(m_top_right, speed); break;
                case 6: m_text->move_to_linear(m_bottom_left, speed); break;
                case 7: m_text->move_to_linear(m_top_left, speed); break;
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
