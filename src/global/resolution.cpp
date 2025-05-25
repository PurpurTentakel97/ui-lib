//
// Purpur Tentakel
// 25.05.25
//

#include <uil/global/resolution.hpp>

namespace uil {
    void ResolutionManager::set_resolution(Resolution const& resolution) {
        m_resolution        = resolution;
        m_resolution_vector = vec_from_resolution(resolution);
    }

    void ResolutionManager::set_custom_resolution(cpt::Vec2_i const& resolution) {
        m_resolution_vector = resolution;
    }

    Resolution ResolutionManager::resolution() const {
        return m_resolution;
    }

    cpt::Vec2_i ResolutionManager::custom_resolution_vector() const {
        return m_custom_resolution_vec;
    }

    cpt::Vec2_i ResolutionManager::resolution_vector() const {
        return m_resolution_vector;
    }

    std::string ResolutionManager::resolution_string() const {
        return str_from_resolution(m_resolution);
    }
}
