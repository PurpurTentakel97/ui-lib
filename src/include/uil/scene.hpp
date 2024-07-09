//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <memory>
#include <uil/ui_element.hpp>
#include <vector>

namespace uil {
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
        Scene()                        = default;
        Scene(Scene const&)            = delete;
        Scene(Scene&&)                 = delete;
        Scene& operator=(Scene const&) = delete;
        Scene& operator=(Scene&&)      = delete;
        virtual ~Scene()               = default;

        [[nodiscard]] virtual bool check(Vector2 const& mousePosition) const;
        [[nodiscard]] virtual bool update() const;
        [[nodiscard]] virtual bool render(Font const* font) const;
        virtual void resize(cpt::Vec2_i const& resolution) const;
    };
}; // namespace uil
