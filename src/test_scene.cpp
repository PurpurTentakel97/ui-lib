//
// Purpur Tentakel
// 06.07.24
//

#include <uil/test_scene.hpp>
#include <uil/text.hpp>


namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution) {
        add_element(std::make_unique<Text>(
                Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f }, Alignment::MidMid, resolution, 0.1f, "Bester Text"));
    }
} // namespace uil
