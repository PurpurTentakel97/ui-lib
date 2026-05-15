//
// Created by marti on 19.06.2025.
//

#pragma once
#include <uil/global/scene.hpp>
#include <uil/elements/button.hpp>

namespace uil {
    class Button;
}


class ButtonTestScene final : public uil::Scene {
private:
    std::weak_ptr<uil::Button> m_button_1;
    std::weak_ptr<uil::Button> m_button_2;

    [[nodiscard]] static uil::ButtonAssetConfig gen_button_asset_config();

public:
    ButtonTestScene();
};
