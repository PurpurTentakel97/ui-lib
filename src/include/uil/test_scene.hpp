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

    public:
        explicit TestScene(cpt::Vec2_i resolution);
    };
} // namespace uil
