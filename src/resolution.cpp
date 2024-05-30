//
// Purpur Tentakel
// 24.05.24
//

#include <format>
#include <raylib.h>
#include <uil/exception.hpp>
#include <uil/resolution.hpp>
#include <functional>

namespace uil {
    cpt::Vec2_i vec_from_resolution(Resolution const resolution) {
        switch (resolution) {
                // clang-format off
            // 16:9
            case Resolution::QUAD_UHD:  return { 15360, 8640 };
            case Resolution::FULL_UHD:  return { 7680,  4320 };
            case Resolution::UHD_Plus:  return { 5120,  2880 };
            case Resolution::UHD:       return { 3840,  2160 };
            case Resolution::WQHD:      return { 2560,  1440 };
            case Resolution::FULL_HD:   return { 1920,  1080 };
            case Resolution::HD:        return { 1280,  720  };
            case Resolution::HD_540:    return { 960,   540  };
            case Resolution::HD_360:    return { 640,   360  };

            // 18:9
            case Resolution::Quad_HD_Plus: return { 2880, 1440 };
            case Resolution::FULL_HD_Plus: return { 2160, 1080 };

            // 21:9
            case Resolution::WUHD:  return { 5120, 2160 };
            case Resolution::UWQHD: return { 3440, 1440 };
            case Resolution::UWFHD: return { 2560, 1080 };

            // 4:3
            case Resolution::HUXGA:      return { 6400, 4800 };
            case Resolution::HXGA:       return { 4096, 3072 };
            case Resolution::QUXGA:      return { 3200, 2400 };
            case Resolution::QSXGA_Plus: return { 2800, 2100 };
            case Resolution::QXGA:       return { 2048, 1536 };
            case Resolution::UXGA:       return { 1600, 1200 };
            case Resolution::SXGA_Plus:  return { 1400, 1050 };
            case Resolution::SXVGA:      return { 1280, 960  };
            case Resolution::XGA:        return { 1024, 768  };
            case Resolution::SVGA:       return { 800,  600  };
            case Resolution::VGA:        return { 640,  480  };
            case Resolution::QSVGA:      return { 400,  300  };
            case Resolution::QVGA:       return { 320,  240  };
                // clang-format on

            case Resolution::SCREEN: {
                auto const screen{ GetCurrentMonitor() };
                auto const height{ GetMonitorHeight(screen) };
                auto const width{ GetMonitorWidth(screen) };

                return { width, height };
            }
            // case Resolution::CUSTOM: return current_resolution;
        }
        throw BadResolution("unexpected resolution in vec switch case");
    }

    std::string str_from_resolution(Resolution resolution) {
        auto const res = std::invoke([resolution] {
            try {
                return vec_from_resolution(resolution);
            } catch (BadResolution const&) { throw BadResolution("unexpected resolution in string switch case"); }
        });
        switch (resolution) {
                // clang-format off
            // 16:9
            case Resolution::QUAD_UHD: return std::format("QUAD_UHD ({} x {})", res.x, res.y);
            case Resolution::FULL_UHD: return std::format("FULL_UHD ({} x {})", res.x, res.y);
            case Resolution::UHD_Plus: return std::format("UHD_Plus ({} x {})", res.x, res.y);
            case Resolution::UHD:      return std::format("UHD ({} x {})",      res.x, res.y);
            case Resolution::WQHD:     return std::format("WQHD ({} x {})",     res.x, res.y);
            case Resolution::FULL_HD:  return std::format("FULL_HD ({} x {})",  res.x, res.y);
            case Resolution::HD:       return std::format("HD ({} x {})",       res.x, res.y);
            case Resolution::HD_540:   return std::format("HD_540 ({} x {})",   res.x, res.y);
            case Resolution::HD_360:   return std::format("HD_360 ({} x {})",   res.x, res.y);

            // 18:9
            case Resolution::FULL_HD_Plus: return std::format("FULL_HD_Plus ({} x {})", res.x, res.y);
            case Resolution::Quad_HD_Plus: return std::format("Quad_HD_Plus ({} x {})", res.x, res.y);

            // 21:9
            case Resolution::UWQHD: return std::format("UWQHD ({} x {})", res.x, res.y);
            case Resolution::WUHD:  return std::format("WUHD ({} x {})",  res.x, res.y);
            case Resolution::UWFHD: return std::format("UWFHD ({} x {})", res.x, res.y);

            // 4:3
            case Resolution::HUXGA:      return std::format("HUXGA ({} x {})",      res.x, res.y);
            case Resolution::HXGA:       return std::format("HXGA ({} x {})",       res.x, res.y);
            case Resolution::QUXGA:      return std::format("QUXGA ({} x {})",      res.x, res.y);
            case Resolution::QSXGA_Plus: return std::format("QSXGA_Plus ({} x {})", res.x, res.y);
            case Resolution::QXGA:       return std::format("QXGA ({} x {})",       res.x, res.y);
            case Resolution::UXGA:       return std::format("UXGA ({} x {})",       res.x, res.y);
            case Resolution::SXGA_Plus:  return std::format("SXGA_Plus ({} x {})",  res.x, res.y);
            case Resolution::SXVGA:      return std::format("SXVGA ({} x {})",      res.x, res.y);
            case Resolution::XGA:        return std::format("XGA ({} x {})",        res.x, res.y);
            case Resolution::SVGA:       return std::format("SVGA ({} x {})",       res.x, res.y);
            case Resolution::VGA:        return std::format("VGA ({} x {})",        res.x, res.y);
            case Resolution::QSVGA:      return std::format("QSVGA ({} x {})",      res.x, res.y);
            case Resolution::QVGA:       return std::format("QVGA ({} x {})",       res.x, res.y);
            case Resolution::SCREEN:     return std::format("SCREEN ({} x {})",     res.x, res.y);
            case Resolution::CUSTOM:     return std::format("CUSTOM ({} x {})",     res.x, res.y);
                // clang-format on
        }
        throw BadResolution("unexpected resolution in string switch case");
    }

    std::vector<std::string> all_string_from_resolution() {
        auto current   = static_cast<Resolution>(0);
        auto const inc = [&current]() -> bool {
            if (current == Resolution::CUSTOM) {
                return false;
            }
            auto temp = static_cast<int>(current);
            ++temp;
            current = static_cast<Resolution>(temp);
            return true;
        };

        std::vector<std::string> to_return{};
        do {
            to_return.emplace_back(str_from_resolution(current));
        } while (inc());

        return to_return;
    }
} // namespace uil
