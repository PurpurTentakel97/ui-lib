//
// Purpur Tentakel
// 24.05.24
//

#include <format>
#include <raylib.h>
#include <uil/exception.hpp>
#include <uil/resolution.hpp>

namespace uil {
    cpt::Vec2_i vec_from_resolution(Resolution const resolution, cpt::Vec2_i current_resolution) {
        switch (resolution) {
                // clang-format off
            // 16:9
            case Resolution::UHD2:    return { 7600, 4320 };
            case Resolution::_5K:     return { 4800, 2700 };
            case Resolution::UHD1:    return { 3840, 2162 };
            case Resolution::WQHD:    return { 2560, 1440 };
            case Resolution::FULL_HD: return { 1920, 1080 };
            case Resolution::HD:      return { 1280, 720  };

            // 21:9
            case Resolution::_5K_ULTRA_WIDE: return { 5120, 2460 };
            case Resolution::UWQHD:          return { 3440, 1440 };
            case Resolution::UWHD:           return { 2560, 1080 };

            // 4:3
            case Resolution::QXGA:      return { 2048, 1536 };
            case Resolution::UXGA:      return { 1600, 1200 };
            case Resolution::XGA:       return { 1024, 768  };
            case Resolution::SVGA:      return { 800,  600  };
            case Resolution::PAL:       return { 768,  576  };
            case Resolution::VGA:       return { 640,  480  };
                // clang-format on

            case Resolution::SCREEN: {
                auto const screen{ GetCurrentMonitor() };
                auto const height{ GetMonitorHeight(screen) };
                auto const width{ GetMonitorWidth(screen) };

                return { width, height };
            }
            case Resolution::CUSTOM: return current_resolution;
        }
        throw BadResolution("unecpected resolution in vec switch case");
    }

    std::string str_from_resolution(Resolution resolution, cpt::Vec2_i current_resolution) {
        auto const res = vec_from_resolution(resolution, current_resolution);
        switch (resolution) {
                // clang-format off
            // 16:9
            case Resolution::UHD2:    return std::format("UHD2: {} x {}",    res.x, res.y);
            case Resolution::_5K:     return std::format("5K: {} x {}",      res.x, res.y);
            case Resolution::UHD1:    return std::format("UHD1: {} x {}",    res.x, res.y);
            case Resolution::WQHD:    return std::format("WQHD: {} x {}",    res.x, res.y);
            case Resolution::FULL_HD: return std::format("Full HD: {} x {}", res.x, res.y);
            case Resolution::HD:      return std::format("HD: {} x {}",      res.x, res.y);

            // 21:9
            case Resolution::_5K_ULTRA_WIDE: return std::format("5k ultra wide: {} x {}", res.x, res.y);
            case Resolution::UWQHD:          return std::format("UWQHD: {} x {}",         res.x, res.y);
            case Resolution::UWHD:           return std::format("UWHD: {} x {}",          res.x, res.y);

            // 4:3
            case Resolution::QXGA:      return std::format("QXGA: {} x {}",      res.x, res.y);
            case Resolution::UXGA:      return std::format("UXGA: {} x {}",      res.x, res.y);
            case Resolution::XGA:       return std::format("XGA: {} x {}",       res.x, res.y);
            case Resolution::SVGA:      return std::format("SVGA: {} x {}",      res.x, res.y);
            case Resolution::PAL:       return std::format("PAL: {} x {}",       res.x, res.y);
            case Resolution::VGA:       return std::format("VGA: {} x {}",       res.x, res.y);

            case Resolution::SCREEN: return std::format("Screen: {} x {}", res.x, res.y);
            case Resolution::CUSTOM: return std::format("Custom: {} x {}", res.x, res.y);
                // clang-format on
        }
        throw BadResolution("unexpected resolution in string switch case");
    }

    std::vector<std::string> all_string_from_resolution(cpt::Vec2_i const current_resolution) {
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
            to_return.emplace_back(str_from_resolution(current, current_resolution));
        } while (inc());

        return to_return;
    }
} // namespace uil
