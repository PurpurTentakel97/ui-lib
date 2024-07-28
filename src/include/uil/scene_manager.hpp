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
        template<std::derived_from<Scene> T, typename... Args>
        T& emplace_scene(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto elem = std::make_unique<T>(std::forward<Args>(args)...);
            auto const temp = elem.get();
            m_scenes.push_back(std::move(elem));
            return *temp;
        }

        [[nodiscard]] bool check(Context const& context) const;
        [[nodiscard]] bool update(Context const& context) const;
        [[nodiscard]] bool render(Context const& context) const;
        void resize(Context const& context) const;
    };
} // namespace uil
