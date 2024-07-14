//
// Purpur Tentakel
// 23.05.24
//

#include "uil/helper_rect.hpp"
#include <uil/alignment.hpp>
#include <uil/exception.hpp>

namespace uil {
    Rectangle aligned_position(Rectangle relative, Alignment const alignment) {
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
                throw BadAlignment("invalid alignment enum while aligning rectangle");
                // clang-format on
        }
        return relative;
    }

    Rectangle aligned_position_reversed(Rectangle relative, Alignment const alignment) {
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
                throw BadAlignment("invalid alignment enum while reversed aligning rectangle");
                // clang-format on
        }

        return relative;
    }

    Rectangle horizontal_aligned_position(Rectangle relative, HorizontalAlignment const alignment) {
        switch (alignment) {
                // clang-format off
            case HorizontalAlignment::Left:
                break;
            case HorizontalAlignment::Mid:
                relative.x -= relative.width / 2;
                break;
            case HorizontalAlignment::Right:
                relative.x -= relative.width;
                break;
            default:
                throw BadAlignment("invalid horizontal alignmend enum while aligning rectanlge horizonalty");
                // clang-format on
        }

        return relative;
    }

    Rectangle horizontal_aligned_position_reversed(Rectangle relative, HorizontalAlignment const alignment) {
        switch (alignment) {
                // clang-format off
            case HorizontalAlignment::Left:
                break;
            case HorizontalAlignment::Mid:
                relative.x += relative.width / 2;
                break;
            case HorizontalAlignment::Right:
                relative.x += relative.width;
                break;
            default:
                throw BadAlignment("invalid horizontal alignmend enum while reversed aligning rectanlge horizonalty");
                // clang-format on
        }

        return relative;
    }

    Rectangle vertical_aligned_position(Rectangle relative, VerticalAlignment const alignment) {
        switch (alignment) {
                // clang-format off
            case VerticalAlignment::Top:
                break;
            case VerticalAlignment::Mid:
                relative.y -= relative.height / 2;
                break;
            case VerticalAlignment::Bottom:
                relative.y -= relative.height;
                break;
            default:
                throw BadAlignment("invalid vertical alignmend enum while aligning rectanlge verticaly");
                // clang-format on
        }

        return relative;
    }

    Rectangle vertical_aligned_position_reversed(Rectangle relative, VerticalAlignment const alignment) {
        switch (alignment) {
                // clang-format off
            case VerticalAlignment::Top:
                break;
            case VerticalAlignment::Mid:
                relative.y += relative.height / 2;
                break;
            case VerticalAlignment::Bottom:
                relative.y += relative.height;
                break;
            default:
                throw BadAlignment("invalid vertical alignmend enum while reversed aligning rectanlge verticaly");
                // clang-format on
        }

        return relative;
    }

    Vector2 aligned_position(Vector2 const& point, Vector2 const& size, Alignment const& alignment) {
        auto const temp = aligned_position(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    Vector2 aligned_position_reversed(Vector2 const& point, Vector2 const& size, Alignment const& alignment) {
        auto const temp = aligned_position_reversed(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    Vector2 horizontal_aligned_position(Vector2 const& point,
                                        Vector2 const& size,
                                        HorizontalAlignment const& alignment) {
        auto const temp = horizontal_aligned_position(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    Vector2 horizontal_aligned_position_reversed(Vector2 const& point,
                                                 Vector2 const& size,
                                                 HorizontalAlignment const& alignment) {
        auto const temp = horizontal_aligned_position_reversed(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    Vector2 vertical_aligned_position(Vector2 const& point, Vector2 const& size, VerticalAlignment const& alignment) {
        auto const temp = vertical_aligned_position(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    Vector2 vertical_aligned_position_reversed(Vector2 const& point,
                                               Vector2 const& size,
                                               VerticalAlignment const& alignment) {
        auto const temp = vertical_aligned_position_reversed(rect_from_point_and_size(point, size), alignment);
        return point_from_rect(temp);
    }

    HorizontalAlignment to_horizontal_alignment(Alignment const alignment) {
        switch (alignment) {
            case Alignment::TopLeft:
            case Alignment::MidLeft:
            case Alignment::BottomLeft: return HorizontalAlignment::Left;

            case Alignment::TopMid:
            case Alignment::MidMid:
            case Alignment::BottomMid: return HorizontalAlignment::Mid;

            case Alignment::TopRight:
            case Alignment::MidRight:
            case Alignment::BottomRight: return HorizontalAlignment::Right;

            default:
                throw BadAlignment(
                        "invalid alignment enum while converting a aligment enum to a horizontal alignment enum");
        }
    }

    VerticalAlignment to_vertical_alignment(Alignment const alignment) {
        switch (alignment) {
            case Alignment::TopLeft:
            case Alignment::TopMid:
            case Alignment::TopRight: return VerticalAlignment::Top;

            case Alignment::MidLeft:
            case Alignment::MidMid:
            case Alignment::MidRight: return VerticalAlignment::Mid;

            case Alignment::BottomLeft:
            case Alignment::BottomMid:
            case Alignment::BottomRight: return VerticalAlignment::Bottom;

            default:
                throw BadAlignment(
                        "invalid alignment enum while converting a aligment enum to a vertical alignment enum");
        }
    }

    Alignment to_alignment(VerticalAlignment const vertical_alignment, HorizontalAlignment const horizontal_alignment) {
        switch (vertical_alignment) {
            case VerticalAlignment::Top:
                switch (horizontal_alignment) {
                    case HorizontalAlignment::Left: return Alignment::TopLeft;
                    case HorizontalAlignment::Mid: return Alignment::TopMid;
                    case HorizontalAlignment::Right: return Alignment::TopRight;
                    default:
                        throw BadAlignment(
                                "invalis horizontal alignment enum while converting to a alignment enum with vertical "
                                "top enum");
                }
            case VerticalAlignment::Mid:
                switch (horizontal_alignment) {
                    case HorizontalAlignment::Left: return Alignment::MidLeft;
                    case HorizontalAlignment::Mid: return Alignment::MidMid;
                    case HorizontalAlignment::Right: return Alignment::MidRight;
                    default:
                        throw BadAlignment(
                                "invalis horizontal alignment enum while converting to a alignment enum with vertical "
                                "mid enum");
                }
            case VerticalAlignment::Bottom:
                switch (horizontal_alignment) {
                    case HorizontalAlignment::Left: return Alignment::BottomLeft;
                    case HorizontalAlignment::Mid: return Alignment::BottomMid;
                    case HorizontalAlignment::Right: return Alignment::BottomRight;
                    default:
                        throw BadAlignment(
                                "invalis horizontal alignment enum while converting to a alignment enum with vertical "
                                "bottom enum");
                }
            default: throw BadAlignment("invalid vertical alignment enum while converting to a alignment enum");
        }
    }
} // namespace uil
