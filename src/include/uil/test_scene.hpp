//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <uil/scene.hpp>
#include <cpt/vec2.hpp>

namespace uil {
    class TestScene final : public Scene {
    private:
    public:
        explicit TestScene(cpt::Vec2_i resolution);
    };
} // namespace uil
