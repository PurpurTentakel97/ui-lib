//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <memory>
#include <uil/element.hpp>
#include <vector>

namespace uil {
    struct Context;

    class Scene {
    private:
        std::vector<std::unique_ptr<UIElement>> m_elements{};

    protected:
        template<std::derived_from<UIElement> T, typename... Args>
        T& emplace_element(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto elem       = std::make_unique<T>(std::forward<Args>(args)...);
            auto const temp = elem.get();
            m_elements.push_back(std::move(elem));
            return *temp;
        }

    public:
        Callback<Scene const&> on_check{};
        Callback<Scene const&> on_update{};
        Callback<Scene const&> on_render{};
        Callback<Scene const&> on_resize{};

        Scene()                        = default;
        Scene(Scene const&)            = delete;
        Scene(Scene&&)                 = delete;
        Scene& operator=(Scene const&) = delete;
        Scene& operator=(Scene&&)      = delete;
        virtual ~Scene()               = default;

        [[nodiscard]] virtual bool check(Context const& context) const;
        [[nodiscard]] virtual bool update(Context const& context) const;
        [[nodiscard]] virtual bool render(Context const& context) const;
        virtual void resize(Context const& context) const;
    };
}; // namespace uil
