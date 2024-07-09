//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <memory>
#include <vector>
#include <uil/scene.hpp>

namespace uil {
    class SceneManager final {
    private:
        std::vector<std::unique_ptr<Scene>> m_scenes{};

    public:
        void add_scene(std::unique_ptr<Scene> scene);

        // [[nodiscard]] bool check(Vector2 mousePosition);
        // [[nodiscard]] bool update();
        bool render(Font const* font) const;
        void resize(cpt::Vec2_i const& resolution) const;
    };
} // namespace uil
