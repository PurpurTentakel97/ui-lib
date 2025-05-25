//
// Created by marti on 19.04.2025.
//


#include "music_test_scene.hpp"
#include <ranges>
#include <uil/global/app_context.hpp>
#include <cpt/log.hpp>


MusicTestScene::MusicTestScene(cpt::Vec2_i const resolution) : Scene{ resolution } {
    auto& sound = uil::AppContext::instance().sound();

    m_id_1 = sound.load_music_collection({ "/assets/music/music_1.mp3",
                                           "/assets/music/music_2.mp3",
                                           "/assets/music/music_3.mp3" }).value_or(0);

    m_id_2 = sound.load_music_collection({ "/assets/music/music_4.mp3" }).value_or(0);
}

bool MusicTestScene::handle_input(uil::UpdateContext const& context) const {
    auto const keep_handle_input = Scene::handle_input(context);

    for (const auto& [rectangle,func] : m_buttons) {
        auto const col = Rectangle{ rectangle.x * static_cast<float>(context.resolution.x),
                                    rectangle.y * static_cast<float>(context.resolution.y),
                                    rectangle.width * static_cast<float>(context.resolution.x),
                                    rectangle.height * static_cast<float>(context.resolution.y) };
        if (CheckCollisionPointRec(context.mouse_position, col)) {
            if (uil::AppContext::instance().input().is_pressed(uil::Mouse::MOUSE_BUTTON_LEFT)) {
                func();
            }
        }
    }

    return keep_handle_input;
}

void MusicTestScene::render(const uil::UpdateContext& context) const {
    Scene::render(context);

    auto const labels = {
        " start 1",
        " start 2",
        " pause",
        " resume",
        " stopp",
        " switch 1",
        " switch 2",
    };

    if (m_buttons.size() != labels.size()) {
        cpt::log::error("Invalid number of buttons or labels!");
        return;
    }

    for (auto const& [button, label] : std::views::zip(m_buttons, labels)) {
        auto const rect = button.first;
        auto const col  = Rectangle{ rect.x * static_cast<float>(context.resolution.x),
                                    rect.y * static_cast<float>(context.resolution.y),
                                    rect.width * static_cast<float>(context.resolution.x),
                                    rect.height * static_cast<float>(context.resolution.y) };

        DrawRectangleLinesEx(col, 1.0f, WHITE);
        DrawText(label, static_cast<int>(col.x), static_cast<int>(col.y), 30,WHITE);
    }
}
