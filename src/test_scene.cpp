//
// Purpur Tentakel
// 06.07.24
//

#include <uil/test_element.hpp>
#include <uil/test_scene.hpp>

namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution) {
        add_element(std::make_unique<TestElement>(
                Rectangle{ 0.5f, 0.5f, 0.7f, 0.7f }, Alignment::MidMid, resolution, false));
        add_element(std::make_unique<TestElement>(
                Rectangle{ 0.5f, 0.5f, 0.5f, 0.5f }, Alignment::MidMid, resolution, true));
    }
} // namespace uil
