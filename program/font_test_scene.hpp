//
// Purpur Tentakel
// 25.05.25
//

#pragma once

#include <uil/scene.hpp>

class FontTestScene final : public uil::Scene {
private:
    cpt::usize m_font_id_1;
    cpt::usize m_font_id_2;

public:
    explicit FontTestScene();

    void render(uil::UpdateContext const& context) const override;
};
