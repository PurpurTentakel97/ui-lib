//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/scene.hpp>

/**
 * no documentation here.
 * this is just for testing.
 * it will change all the time.
 */
class TestScene final : public uil::Scene {
private:
public:
    TestScene(cpt::Vec2_i resolution, Color c, Vector2 pos);

    [[nodiscard]] bool handle_input(uil::Context const& context) const override;
};
