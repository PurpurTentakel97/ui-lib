//
// Purpur Tentakel
// 06.07.24
//

#include <iostream>
#include <string>
#include <uil/elements/link.hpp>
#include <uil/scenes/test_scene.hpp>

namespace uil {

    void TestScene::on_click(Text&) {
        std::cout << "click\n";
    }

    void TestScene::on_first_click(Text&) {
        std::cout << "first click\n";
    }

    void TestScene::on_hover(Text&) {
        std::cout << "hover\n";
    }

    TestScene::TestScene(cpt::Vec2_i const resolution, int const t) : Scene{ resolution } {

        std::cout << "Test T: " << t << '\n';

        auto const raw_text = std::string(
                "Bavaria ipsum dolor sit amet Wurscht wann griagd ma nacha wos z’dringa oans, auf gehds beim Schichtl "
                "Hendl wo hi o’ha hoam dahoam: Barfuaßat Namidog spernzaln measi Auffisteign Musi, Oachkatzlschwoaf "
                "dahoam af schaugn oans. Auffisteign ebba wos hod schüds nei d’ hea nix hoid. Weibaleid schüds nei "
                "trihöleridi dijidiholleri griasd eich midnand Gamsbart Sauakraud etza unbandig Stubn a so a Schmarn!\n"
                "Ham allerweil Bussal Ewig und drei Dog naa jo mei is des schee, hallelujah sog i, luja sog i! "
                "Gamsbart umananda wo hi Schuabladdla und sei Charivari hawadere midananda Fingahaggln aasgem, sowos "
                "obandln. Sog i zua Sauwedda Reiwadatschi i hob di liab i moan oiwei wiavui Schorsch, a ganze Radi. "
                "Wos obandln nix Gwiass woass ma ned oamoi und sei hawadere midananda Broadwurschtbudn trihöleridi "
                "dijidiholleri. Und jedza moand, !");


        [[maybe_unused]] auto const text
                = &emplace_element<Link>(Rectangle{ 0.25f, 0.25f, 0.3f, 0.3f }, Alignment::MidMid, resolution);
        text->set_text(raw_text);
        text->set_text_alignment(Alignment::MidMid);
        text->set_breaking(true);
        text->update_text();
        text->on_click += [this](Text& te) { this->on_click(te); };
        text->on_first_click += [this](Text& te) { this->on_first_click(te); };
        text->on_hover += [this](Text& te) { this->on_hover(te); };
        text->move_to_linear_time({ 0.75f, 0.75f }, 10.0f);
    }

} // namespace uil
