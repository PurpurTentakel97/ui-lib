//
// Purpur Tentakel
// 06.07.24
//

#include <uil/test_scene.hpp>
#include <uil/text.hpp>


namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution) {
        m_text = &emplace_element<Text>(Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f }, Alignment::MidMid, resolution, 0.1f);
        m_text->set_color(PURPLE)
            .set_spacing(3.0f)
            .set_text("Bester Text")
            .set_render_collider(true);
    }
} // namespace uil
