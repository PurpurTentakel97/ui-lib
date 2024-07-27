//
// Purpur Tentakel
// 06.07.24
//


#include <array>
#include <string>
#include <uil/test_scene.hpp>
#include <uil/text.hpp>

namespace uil {

    TestScene::TestScene(cpt::Vec2_i const resolution) {

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

        auto constexpr points = std::array<Vector2, 9>{
            Vector2{ 0.16f, 0.16f },
            Vector2{ 0.5f,  0.16f },
            Vector2{ 0.83f, 0.16f },
            Vector2{ 0.16f, 0.5f  },
            Vector2{ 0.5f,  0.5f  },
            Vector2{ 0.83f, 0.5f  },
            Vector2{ 0.16f, 0.83f },
            Vector2{ 0.5f,  0.83f },
            Vector2{ 0.83f, 0.83f },
        };

        // clang-format off
        auto constexpr alignment = std::array<Alignment,9>{
            Alignment::TopLeft,
            Alignment::TopMid,
            Alignment::TopRight,
            Alignment::MidLeft,
            Alignment::MidMid,
            Alignment::MidRight,
            Alignment::BottomLeft,
            Alignment::BottomMid,
            Alignment::BottomRight,
        };
        // clang-format on

        for (cpt::usize i = 0; i < 9; ++i) {
            [[maybe_unused]] auto const text = &emplace_element<Text>(
                    Rectangle{ points[i].x, points[i].y, 0.3f, 0.3f }, Alignment::MidMid, resolution);
            text->set_text(raw_text);
            // text->set_render_collider_debug(true);
            text->set_text_alignment(alignment[i]);
            text->set_breaking(true);
            text->update_text();
            // text->set_render_line_collider_debug(true);
        }
    }

} // namespace uil
