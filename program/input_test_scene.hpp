//
// Created by marti on 19.04.2025.
//

#pragma once

#include <uil/scene.hpp>
#include <uil/element.hpp>
#include <uil/global/app_context.hpp>

class InputTestObject final : public uil::UIElement {
private:
    bool m_render{};
    std::function<bool()> check_function;

public:
    InputTestObject(Rectangle const relative,
                    uil::Alignment const alignment,
                    std::function<bool()> const& check_function_)
        : UIElement{ relative, alignment }, check_function{ check_function_ } {}

    using UIElement::UIElement;

    [[nodiscard]] bool handle_input(const uil::UpdateContext& context) override {
        auto const keep_updating = UIElement::handle_input(context);

        m_render = check_function();

        return keep_updating;
    }

    void render(const uil::UpdateContext& context) const override {
        UIElement::render(context);

        m_render ? DrawRectangleRec(collider(),GREEN) : DrawRectangleRec(collider(),RED);
    }
};

class InputTestScene final : public uil::Scene {
private:
    struct Entry final {
        Rectangle relative;
        std::function<bool()> function;
    };

    auto static constexpr s_key_1 = uil::Mouse::MOUSE_BUTTON_LEFT;
    auto static constexpr s_key_2 = uil::Mouse::MOUSE_BUTTON_RIGHT;
    auto static constexpr s_mod_1 = uil::KeyboardMod::KEY_LEFT_SHIFT;
    auto static constexpr s_mod_2 = uil::KeyboardMod::KEY_LEFT_CONTROL;

    Rectangle static constexpr rectangle_mouse_input = { 0.1f, 0.15f, 0.02f, 0.04f };
    Vector2 static constexpr spacer_mouse_input      = { 0.01f, 0.01f };

    static constexpr float x(Rectangle const rectangle, Vector2 const spacer, int const columns) {
        return rectangle.x
               + static_cast<float>(columns) * spacer.x
               + static_cast<float>(columns) * rectangle.width;
    }

    static constexpr float y(Rectangle const rectangle, Vector2 const spacer, int const rows) {
        return rectangle.y
               + static_cast<float>(rows) * spacer.y
               + static_cast<float>(rows) * rectangle.height;
    }

    std::vector<Entry> const m_entries{
        // is_down
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 0), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 1), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down<uil::KeyOp::And>(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 2), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down<uil::KeyOp::Or, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 3), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down<uil::KeyOp::And, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 4), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down(s_key_1, s_key_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 0), y(rectangle_mouse_input, spacer_mouse_input, 5), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_down<uil::KeyOp::And>(s_key_1, s_key_2);
          } },

        // is_up
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 0), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 1), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up<uil::KeyOp::And>(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 2), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up<uil::KeyOp::Or, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 3), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up<uil::KeyOp::And, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 4), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up(s_key_1, s_key_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 1), y(rectangle_mouse_input, spacer_mouse_input, 5), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_up<uil::KeyOp::And>(s_key_1, s_key_2);
          } },

        // is_pressed
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 0), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 1), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed<uil::KeyOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 2), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed<uil::KeyOp::Or, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 3), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed<uil::KeyOp::And, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 4), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed(s_key_1, s_key_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 2), y(rectangle_mouse_input, spacer_mouse_input, 5), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_pressed<uil::KeyOp::And>(s_key_1, s_key_2);
          } },

        // is_released
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 0), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released(s_key_1, s_key_2, s_mod_1, s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 1), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released<uil::KeyOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 2), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released<uil::KeyOp::Or, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 3), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released<uil::KeyOp::And, uil::ModOp::And>(
                      s_key_1,
                      s_key_2,
                      s_mod_1,
                      s_mod_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 4), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released(s_key_1, s_key_2);
          } },
        { { x(rectangle_mouse_input, spacer_mouse_input, 3), y(rectangle_mouse_input, spacer_mouse_input, 5), rectangle_mouse_input.width, rectangle_mouse_input.height },
          []() -> bool {
              return uil::AppContext::instance().input().is_released<uil::KeyOp::And>(s_key_1, s_key_2);
          } },
    };

public:
    explicit InputTestScene();

    void render(const uil::UpdateContext& context) const override;
};
