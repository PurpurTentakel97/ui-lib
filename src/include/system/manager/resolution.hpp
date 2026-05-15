//
// Purpur Tentakel
// 25.05.25
//

#pragma once
#include <cpt/vec2.hpp>
#include <uil/global/resolution_enum.hpp>

namespace uil::sys {
    class ResolutionManager final {
    private:
        Resolution m_resolution{ Resolution::SVGA };
        cpt::Vec2_i m_resolution_vector{ vec_from_resolution(Resolution::SVGA) };
        cpt::Vec2_i m_custom_resolution_vec{ 600, 800 };

    public:
        void set_resolution(Resolution const& resolution);
        void set_custom_resolution(cpt::Vec2_i const& resolution);

        [[nodiscard]] Resolution resolution() const;
        [[nodiscard]] cpt::Vec2_i custom_resolution_vector() const;
        [[nodiscard]] cpt::Vec2_i resolution_vector() const;
        [[nodiscard]] std::string resolution_string() const;
    };
} // namespace uil::sys
