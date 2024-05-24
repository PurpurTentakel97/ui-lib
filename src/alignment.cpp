//
// Purpur Tentakel
// 23.05.24
//

#include <uil/alignment.hpp>
#include <uil/exception.hpp>

namespace uil {
    Rect aligned_position(Rect relative, Alignment alignment) {
        switch (alignment) {
                // clang-format off
            case Alignment::TopLeft:
                break;
            case Alignment::TopMid:
                relative.x -= relative.width / 2;
                break;
            case Alignment::TopRight:
                relative.x -= relative.width;
                break;
            case Alignment::MidLeft:
                relative.y -= relative.height / 2;
                break;
            case Alignment::MidMid:
                relative.y -= relative.height / 2;
                relative.x -= relative.width / 2;
                break;
            case Alignment::MidRight:
                relative.y -= relative.height / 2;
                relative.x -= relative.width;
                break;
            case Alignment::BottomLeft:
                relative.y -= relative.height;
                break;
            case Alignment::BottomMid:
                relative.y -= relative.height;
                relative.x -= relative.width / 2;
                break;
            case Alignment::BottomRight:
                relative.y -= relative.height;
                relative.x -= relative.width;
                break;
            default:
                throw BadAlignment("invalid alignment enum");
                // clang-format on
        }
        return relative;
    }

    Rect aligned_position_reversed(Rect relative, Alignment alignment) {
        switch (alignment) {
                // clang-format off
            case Alignment::TopLeft:
                break;
            case Alignment::TopMid:
                relative.x += relative.width / 2;
                break;
            case Alignment::TopRight:
                relative.x += relative.width;
                break;
            case Alignment::MidLeft:
                relative.y += relative.height / 2;
                break;
            case Alignment::MidMid:
                relative.x += relative.width / 2;
                relative.y += relative.height / 2;
                break;
            case Alignment::MidRight:
                relative.x += relative.width;
                relative.y += relative.height / 2;
                break;
            case Alignment::BottomLeft:
                relative.y += relative.height;
                break;
            case Alignment::BottomMid:
                relative.x += relative.width / 2;
                relative.y += relative.height;
                break;
            case Alignment::BottomRight:
                relative.x += relative.width;
                relative.y += relative.height;
                break;
            default:
                throw BadAlignment("invalid alignment enum");
                // clang-format on
        }

        return relative;
    }
} // namespace uil
