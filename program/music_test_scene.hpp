//
// Created by marti on 19.04.2025.
//

#pragma once

#include <uil/scene.hpp>
#include <uil/global/sound.hpp>
#include <uil/global/app_context.hpp>

static constexpr float x(Rectangle const& start, int const column, float const spacer) {
    return start.x + static_cast<float>(column) * start.width + static_cast<float>(column) * spacer;
}

static constexpr float y(Rectangle const& start, int const row, float const spacer) {
    return start.y + static_cast<float>(row) * start.height + static_cast<float>(row) * spacer;
}

class MusicTestScene final : public uil::Scene {
private:
    cpt::usize m_id_1{};
    cpt::usize m_id_2{};

    static constexpr Rectangle s_size{ 0.1f, 0.1f, 0.1f, 0.1f };
    static constexpr float s_spacer{ 0.05f };

    static constexpr Rectangle s_start_1{ x(s_size, 0, s_spacer), y(s_size, 0, s_spacer), s_size.width, s_size.height };
    static constexpr Rectangle s_start_2{ x(s_size, 1, s_spacer), y(s_size, 0, s_spacer), s_size.width, s_size.height };
    static constexpr Rectangle s_pause_1{ x(s_size, 0, s_spacer), y(s_size, 1, s_spacer), s_size.width, s_size.height };
    static constexpr Rectangle s_resume_1{ x(s_size, 0, s_spacer), y(s_size, 2, s_spacer), s_size.width,
                                           s_size.height };
    static constexpr Rectangle s_end_1{ x(s_size, 0, s_spacer), y(s_size, 3, s_spacer), s_size.width, s_size.height };
    static constexpr Rectangle s_switch_1{ x(s_size, 0, s_spacer), y(s_size, 4, s_spacer), s_size.width,
                                           s_size.height };
    static constexpr Rectangle s_switch_2{ x(s_size, 1, s_spacer), y(s_size, 4, s_spacer), s_size.width,
                                           s_size.height };

    std::vector<std::pair<Rectangle, std::function<uil::SoundManager::Result()>>> m_buttons{
        { s_start_1, [this]() { return uil::AppContext::instance().sound().start_music_collection(m_id_1); } },
        { s_start_2, [this]() { return uil::AppContext::instance().sound().start_music_collection(m_id_2); } },
        { s_pause_1, []() { return uil::AppContext::instance().sound().pause_music_collection(); } },
        { s_resume_1, []() { return uil::AppContext::instance().sound().resume_music_collection(); } },
        { s_end_1, []() { return uil::AppContext::instance().sound().stop_music_collection(); } },
        { s_switch_1, [this]() { return uil::AppContext::instance().sound().switch_music_collection(m_id_1); } },
        { s_switch_2, [this]() { return uil::AppContext::instance().sound().switch_music_collection(m_id_2); } },
    };

public:
    explicit MusicTestScene();

    [[nodiscard]] bool handle_input(uil::UpdateContext const& context) const override;
    void render(const uil::UpdateContext& context) const override;
};
