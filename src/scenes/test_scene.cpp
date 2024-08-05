//
// Purpur Tentakel
// 06.07.24
//

#include <array>
#include <uil/elements/test_element.hpp>
#include <uil/scenes/test_scene.hpp>

namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution, int const t) : Scene{ resolution } {
        auto constexpr colors = std::array<Color, 4>{
            RED,
            BLUE,
            PINK,
            GREEN,
        };

        [[maybe_unused]] auto const text
                = &emplace_element<TestElement>(Rectangle{ 0.2f * static_cast<float>(t), 0.25f, 0.3f, 0.3f },
                                                Alignment::MidMid,
                                                resolution,
                                                colors[static_cast<cpt::usize>(t - 1)]);
        text->move_to_linear_time({ 0.75f, 0.75f }, 10.0f);
    }

} // namespace uil
