//
// Purpur Tentakel
// 25.05.25
//

#include "font_test_scene.hpp"
#include <uil/global/app_context.hpp>


FontTestScene::FontTestScene() {
    auto& font  = uil::AppContext::instance().font();
    m_font_id_1 = font.load("/assets/font/font.ttf").value_or(0);
    m_font_id_2 = font.load("/assets/font/invalid.ttf").value_or(0);
}

void FontTestScene::render() const {
    Scene::render();
    auto const& font = uil::AppContext::instance().font();

    auto const& font_1 = font.get(m_font_id_1);
    DrawTextEx(font_1, "Hello World!", { 100.0f, 100.0f }, 20.0f, 1.0f, WHITE);

    auto const& font_2 = font.get(m_font_id_2);
    DrawTextEx(font_2, "Hello World!", { 100.0f, 200.0f }, 20.0f, 1.0f, WHITE);
}
