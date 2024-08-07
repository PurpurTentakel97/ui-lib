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
    public:
        TestScene(cpt::Vec2_i resolution, Color c, Vector2 pos);
    };
} // namespace uil
