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

        auto constexpr top_left     = Vector2(0.25f, 0.25f);
        auto constexpr bottom_left  = Vector2(0.25f, 0.75f);
        auto constexpr bottom_right = Vector2(0.75f, 0.75f);
        auto constexpr top_right    = Vector2(0.75f, 0.25f);
        auto constexpr speed        = 0.1f;
        static auto index           = 0;
        auto const inc              = [&i = index]() {
            ++i;
            if (index > 4) {
                index = 0;
            }
        };

        if (not m_text->is_moving()) {
            std::cout << index << '\n';
            switch (index) {
                case 0: m_text->move_to_linear(bottom_left, speed); break;
                case 1: m_text->move_to_linear(bottom_right, speed); break;
                case 2: m_text->move_to_linear(top_right, speed); break;
                case 3: m_text->move_to_linear(top_left, speed); break;
            }
            inc();
        }


        return result;
    }
} // namespace uil
