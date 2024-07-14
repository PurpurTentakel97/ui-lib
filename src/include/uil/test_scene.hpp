//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/scene.hpp>

namespace uil {
    class Text;

    class TestScene final : public Scene {
    private:
        Text* m_text{};
        Vector2 m_top_left     = { 0.25f, 0.25f };
        Vector2 m_bottom_left  = { 0.25f, 0.75f };
        Vector2 m_bottom_right = { 0.75f, 0.75f };
        Vector2 m_top_right    = { 0.75f, 0.25f };

        void start_callback(UIElement const& text) const;
        void stop_callback(UIElement const& text) const;
        void arrived_callback(UIElement const& text) const;

    public:
        explicit TestScene(cpt::Vec2_i resolution);

        [[nodiscard]] bool check(Vector2 const& mousePosition) const override;
        [[nodiscard]] bool render(Font const* font) const override;
    };
} // namespace uil
