//
// Created by marti on 17.05.2025.
//

#include "asset_test_scene.hpp"
#include <uil/global/app_context.hpp>

AssetTestScene::AssetTestScene() {
    auto& assets = uil::AppContext::instance().asset();

    m_valid_asset = assets.load("/assets/assets/arrow_down.png").value_or(0);
    m_invalid_asset = assets.load("/assets/assets/invalid.png").value_or(0);
}

void AssetTestScene::render() const {
    Scene::render();
    auto const& assets = uil::AppContext::instance().asset();

    auto const& asset_1 = assets.get(m_valid_asset);
    DrawTexturePro(asset_1, {0.0f,0.0f,static_cast<float>(asset_1.width), static_cast<float>(asset_1.height)}, {100.0f,100.0f,100.0f,100.0f}, {0.0f,0.0f}, 0.0f, WHITE );

    auto const& asset_2 = assets.get(m_invalid_asset);
    DrawTexturePro(asset_2, {0.0f,0.0f,static_cast<float>(asset_2.width), static_cast<float>(asset_2.height)}, {100.0f,250.0f,100.0f,100.0f}, {0.0f,0.0f}, 0.0f, WHITE );
}
