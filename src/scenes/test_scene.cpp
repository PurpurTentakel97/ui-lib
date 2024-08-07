//
// Purpur Tentakel
// 06.07.24
//

#include <uil/elements/test_element.hpp>
#include <uil/elements/text.hpp>
#include <uil/scenes/test_scene.hpp>

namespace uil {
    TestScene::TestScene(cpt::Vec2_i const resolution, [[maybe_unused]] Color const c, Vector2 const pos)
        : Scene{ resolution } {

        auto const t
                = "Bavaria ipsum dolor sit amet nix liberalitas Bavariae ja, wo samma denn jo mei hea des muas ma hoid "
                  "kenna Broadwurschtbudn. Abfieseln nia need Xaver iabaroi i moan oiwei Almrausch Gaudi, i hob di "
                  "liab i hob di liab schoo trihöleridi dijidiholleri! Anbandeln Bradwurschtsemmal Griasnoggalsubbm, "
                  "Hendl Obazda Stubn Zwedschgndadschi Obazda und glei wirds no fui lustiga. Zidern Stubn hea, oans? "
                  "Gor nix Gwiass woass ma ned nimmds Weiznglasl Wiesn? Aba Haberertanz und glei wirds no fui lustiga "
                  "oamoi, nia? Singd san dringma aweng, Schdarmbeaga See Watschnpladdla Schbozal Graudwiggal: Dringma "
                  "aweng i Woibbadinga umananda ozapfa, i hob di narrisch gean is Zidern. Radi oamoi Brotzeit griaß "
                  "God beinand ozapfa heid gfoids ma sagrisch guad und! I sog ja nix, i red ja bloß Ledahosn fei "
                  "liberalitas Bavariae pfiad de heitzdog Vergeltsgott, Guglhupf. Nimmds schoo Schmankal, Kneedl a "
                  "bissal wos gehd ollaweil eana Leonhardifahrt is ma Wuascht.";

        [[maybe_unused]] auto const text
                = emplace_top<Text>(Rectangle{ pos.x, pos.y, 0.5f, 0.5f }, Alignment::TopLeft).lock();
        text->set_font_size(0.02f);
        text->set_text(t);
        text->set_render_collider_debug(true);
        text->set_render_line_collider_debug(true);
        text->set_color(c);
        text->move_to_linear_time({ 0.9f, 0.9f }, 10.0f);

        m_test = emplace_top<TestElement>(Rectangle{ 0.9f, 0.9f, 0.3f, 0.3f }, Alignment::BottomRight, RED).lock();
        m_test->move_to_linear_time({ 0.2f, 0.2f }, 10.0f);
    }

    bool TestScene::handle_input(Context const& context) const {
        auto const keep_handle_input = Scene::handle_input(context);

        m_test->set_active(IsMouseButtonDown(MOUSE_BUTTON_LEFT));

        return keep_handle_input;
    }
} // namespace uil
