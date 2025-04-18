//
// Purpur Tentakel
// 18.04.25
//

#pragma once
#include <filesystem>

namespace uil {
    [[nodiscard]] std::filesystem::path make_absolute_path(std::filesystem::path const& path);
}
