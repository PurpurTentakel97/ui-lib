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
    public:
        TestScene(cpt::Vec2_i resolution, Color c, Vector2 pos);

        [[nodiscard]] bool handle_input(Context const& context) const override;
        [[nodiscard]] bool update(Context const& context) const override;
    };
} // namespace uil
