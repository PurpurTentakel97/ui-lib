//
// Created by marti on 19.04.2025.
//

#include "input_test_scene.hpp"

InputTestScene::InputTestScene(cpt::Vec2_i const resolution) : Scene{ resolution } {
    for (auto const& entry : m_entries) {
        emplace_top<InputTestObject>(entry.relative, uil::Alignment::MidMid, entry.function);
    }
}

void InputTestScene::render(const uil::UpdateContext& context) const {
    Scene::render(context);
    auto const font = GetFontDefault();

    auto const draw_label = [this, &font](Rectangle const rectangle,
                                         Vector2 const spacer,
                                         Vector2 const offset,
                                         int const columns,
                                         int const rows,
                                         float const rotation,
                                         char const* text) {
        DrawTextPro(font,
                    text,
                    { (x(rectangle, spacer, columns) + offset.x) * static_cast<float>(resolution().x),
                      (y(rectangle, spacer, rows) + offset.y) * static_cast<float>(resolution().y) },
                    { 0.0f, 0.0f },
                    rotation,
                    0.02f * static_cast<float>(resolution().y),
                    2.0f,
                    WHITE);
    };

    Vector2 constexpr offset_mouse_left{ -0.07f, 0.01f };
    Vector2 constexpr offset_mouse_top{ 0.005f, -0.01f };

    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 0, 0.0f, "or - or");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 1, 0.0f, "and - or");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 2, 0.0f, "or - and");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 3, 0.0f, "and - and");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 4, 0.0f, "or - none");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_left, 0, 5, 0.0f, "and - none");

    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_top, 0, 0, -90.0f, "is_down");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_top, 1, 0, -90.0f, "is_up");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_top, 2, 0, -90.0f, "is_pressed");
    draw_label(rectangle_mouse_input, spacer_mouse_input, offset_mouse_top, 3, 0, -90.0f, "is_released");

}
