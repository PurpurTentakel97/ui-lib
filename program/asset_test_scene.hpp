//
// Created by marti on 17.05.2025.
//

#pragma once
#include <uil/scene.hpp>

class AssetTestScene final : public uil::Scene {
private:
    cpt::usize m_valid_asset;
    cpt::usize m_invalid_asset;

public:
    explicit AssetTestScene(cpt::Vec2_i resolution);

    void render(uil::UpdateContext const& context) const override;
};
