//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <uil/scene.hpp>
#include <cpt/vec2.hpp>

namespace uil {
    class Text;

    class TestScene final : public Scene {
    private:
        Text* m_text{};
    public:
        explicit TestScene(cpt::Vec2_i resolution);
    };
} // namespace uil
