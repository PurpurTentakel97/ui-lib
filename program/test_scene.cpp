//
// Purpur Tentakel
// 06.07.24
//

#include "test_scene.hpp"
#include <uil/elements/text.hpp>

TestScene::TestScene(cpt::Vec2_i const resolution, [[maybe_unused]] Color const c, Vector2 const pos)
    : Scene{ resolution } {

    auto const t
            = "Bavaria ipsum dolor sit amet nix liberalitas Bavariae ja, wo samma denn jo mei hea des muas ma hoid "
              "kenna Broadwurschtbudn. Abfieseln nia need Xaver iabaroi i moan oiwei Almrausch Gaudi, i hob di "
              "liab i hob di liab schoo trihöleridi dijidiholleri! Anbandeln Bradwurschtsemmal Griasnoggalsubbm, "
              "Hendl Obazda Stubn Zwedschgndadschi Obazda und glei wirds no fui lustiga. Zidern Stubn hea, oans? "
              "Gor nix Gwiass woass ma ned nimmds Weiznglasl Wiesn?\nAba Haberertanz und glei wirds no fui lustiga "
              "oamoi, nia? Singd san dringma aweng, Schdarmbeaga See Watschnpladdla Schbozal Graudwiggal: Dringma "
              "aweng i Woibbadinga umananda ozapfa, i hob di narrisch gean is Zidern. Radi oamoi Brotzeit griaß "
              "God beinand ozapfa heid gfoids ma sagrisch guad und!\nI sog ja nix, i red ja bloß Ledahosn fei "
              "liberalitas Bavariae pfiad de heitzdog Vergeltsgott, Guglhupf. Nimmds schoo Schmankal, Kneedl a "
              "bissal wos gehd ollaweil eana Leonhardifahrt is ma Wuascht.";

    [[maybe_unused]] auto const text
            = emplace_top<uil::Text>(Rectangle{ pos.x, pos.y, 0.5f, 0.5f }, uil::Alignment::TopLeft).lock();
    text->set_font_size(0.02f);
    text->set_text(t);
    text->debug_element.collider.set(true);
    text->debug_text.line_collider.set(true);
    text->debug_element.movement.set(true);
    text->set_color(c);
    text->set_breaking(true);
    text->move_to_linear_time({ 0.9f, 0.9f }, 10.0f);
}

bool TestScene::handle_input(uil::Context const& context) const {
    auto const keep_handle_input = Scene::handle_input(context);
    return keep_handle_input;
}
