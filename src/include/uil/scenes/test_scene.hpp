//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/scene.hpp>

/**
 * no dcumentation here.
 * this is just for testing.
 * it will change all the time.
 */
namespace uil {
    class Text;

    class TestScene final : public Scene {
    private:

        void on_click(Text& text);
        void on_first_click(Text& text);
        void on_hover(Text& text);

    public:
        TestScene(cpt::Vec2_i resolution, int t);
    };
} // namespace uil
