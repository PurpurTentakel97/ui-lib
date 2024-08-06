//
// Purpur Tentakel
// 06.07.24
//

#include <array>
#include <uil/elements/test_element.hpp>
#include <uil/scenes/test_scene.hpp>

namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution, Color const c, Vector2 const pos)
        : Scene{ resolution } {


        [[maybe_unused]] auto const text = &emplace_element<TestElement>(
                Rectangle{ pos.x, pos.y, 0.5f, 0.5f }, Alignment::TopLeft, resolution, c);

        // text->move_to_linear_time({ pos.x + 0.5f, pos.y + 0.5f }, 10.0f);
    }

    bool TestScene::handle_input(Context const& context) const {
        [[maybe_unused]] auto const test = Scene::handle_input(context);
        return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    }
    bool TestScene::update(Context const& context) const {
        [[maybe_unused]] auto const test =  Scene::update(context);
        return IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    }
} // namespace uil
