//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <memory>
#include <uil/scene.hpp>
#include <vector>

namespace uil {
    struct Context;

    class SceneManager final {
    private:
        std::vector<std::unique_ptr<Scene>> m_scenes{};

    public:
        void add_scene(std::unique_ptr<Scene> scene);

        [[nodiscard]] bool check(Context const& context) const;
        [[nodiscard]] bool update(Context const& context) const;
        [[nodiscard]] bool render(Context const& context) const;
        void resize(Context const& context) const;
    };
} // namespace uil
