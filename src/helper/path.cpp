//
// Purpur Tentakel
// 18.04.25
//

#include <uil/helper/path.hpp>

namespace uil {
    std::filesystem::path make_absolute_path(std::filesystem::path const& path) {
        std::filesystem::path full_path{ path };
        if (path.is_relative()) {
            full_path = std::filesystem::current_path() / full_path.relative_path();
        }

        return full_path.make_preferred();
    }
}
