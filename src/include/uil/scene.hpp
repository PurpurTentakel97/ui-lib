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
        void add_element(std::unique_ptr<UIElement> element);

    public:
        Scene()                        = default;
        Scene(Scene const&)            = delete;
        Scene(Scene&&)                 = delete;
        Scene& operator=(Scene const&) = delete;
        Scene& operator=(Scene&&)      = delete;
        virtual ~Scene()               = default;

        // [[nodiscard]] virtual bool check(Vector2 mousePosition);
        // [[nodiscard]] virtual bool update();
        [[nodiscard]] virtual bool render() const;
        // virtual void resize();
    };
}; // namespace uil
