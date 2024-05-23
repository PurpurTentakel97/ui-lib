//
// Purpur Tentakel
// 23.05.24
//

#include <uil/alignment.hpp>
#include <uil/exception.hpp>

namespace uil {
    cpt::Vec2f aligned_position(cpt::Vec2f pos, cpt::Vec2f size, Alignment alignment) {
        switch (alignment) {
                // clang-format off
            case Alignment::TopLeft:
                break;
            case Alignment::TopMid:
                pos.x -= size.x / 2;
                break;
            case Alignment::TopRight:
                pos.x -= size.x;
                break;
            case Alignment::MidLeft:
                pos.y -= size.y / 2;
                break;
            case Alignment::MidMid:
                pos.y -= size.y / 2;
                pos.x -= size.x / 2;
                break;
            case Alignment::MidRight:
                pos.y -= size.y / 2;
                pos.x -= size.x;
                break;
            case Alignment::BottomLeft:
                pos.y -= size.y;
                break;
            case Alignment::BottomMid:
                pos.y -= size.y;
                pos.x -= size.x / 2;
                break;
            case Alignment::BottomRight:
                pos.y -= size.y;
                pos.x -= size.x;
                break;
            default:
                throw BadAlignment("invalid alignment enum");
                // clang-format on
        }
        return pos;
    }
    cpt::Vec2f aligned_position_reversed(cpt::Vec2f pos, cpt::Vec2f size, Alignment alignment) {
        switch (alignment) {
                // clang-format off
            case Alignment::TopLeft:
                break;
            case Alignment::TopMid:
                pos.x += size.x / 2;
                break;
            case Alignment::TopRight:
                pos.x += size.x;
                break;
            case Alignment::MidLeft:
                pos.y += size.y / 2;
                break;
            case Alignment::MidMid:
                pos.x += size.x / 2;
                pos.y += size.y / 2;
                break;
            case Alignment::MidRight:
                pos.x += size.x;
                pos.y += size.y / 2;
                break;
            case Alignment::BottomLeft:
                pos.y += size.y;
                break;
            case Alignment::BottomMid:
                pos.x += size.x / 2;
                pos.y += size.y;
                break;
            case Alignment::BottomRight:
                pos.x += size.x;
                pos.y += size.y;
                break;
            default:
                throw BadAlignment("invalid alignment enum");
                // clang-format on
        }

        return pos;
    }
} // namespace uil
