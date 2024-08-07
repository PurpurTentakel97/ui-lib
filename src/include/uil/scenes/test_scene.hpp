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
    class TestElement;

    class TestScene final : public Scene {
    private:
        std::shared_ptr<TestElement> m_test;
    public:
        TestScene(cpt::Vec2_i resolution, Color c, Vector2 pos);

        [[nodiscard]] bool handle_input(Context const& context) const override;
    };
} // namespace uil
