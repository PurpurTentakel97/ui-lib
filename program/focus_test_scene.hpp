//
// Created by marti on 30.05.2025.
//

#pragma once

#include <uil/focus_element.hpp>
#include <uil/scene.hpp>

struct Element final : uil::FocusElement, uil::UIElement {
    using UIElement::UIElement;

    void render() const override;
};

class FocusTestScene final : public uil::Scene {
private:
    std::vector<std::vector<std::shared_ptr<Element>>> m_focus_elements{};

public:
    FocusTestScene();
};
