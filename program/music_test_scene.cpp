//
// Created by marti on 19.04.2025.
//


#include "music_test_scene.hpp"
#include <ranges>
#include <uil/global/app_context.hpp>


void print_error(uil::SoundManager::Result const result) {
    switch (result) {
        case uil::SoundManager::Result::InvalidPath: {
            std::cout << "[[InvalidPath]] | " << '\n';
            break;
        }
        case uil::SoundManager::Result::EmptyContainer: {
            std::cout << "[[EmptyContainer]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::UnknownLevelID: {
            std::cout << "[[UnknownLevelID]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::UnknownSoundID: {
            std::cout << "[[UnknownSoundID]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::UnknownMusicCollectionID: {
            std::cout << "[[UnknownMusicCollectionID]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::StillMusicPlaying: {
            std::cout << "[[StillMusicPlaying]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::NoMusicPlaying: {
            std::cout << "[[NoMusicPlaying]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::NoCurrentMusic: {
            std::cout << "[[NoCurrentMusic]]" << '\n';
            break;
        }
        case uil::SoundManager::Result::Success: {
            std::cout << "[[Success]]" << '\n';
            break;
        }
    }
}


MusicTestScene::MusicTestScene(cpt::Vec2_i const resolution) : Scene{ resolution } {
    auto& sound = uil::AppContext::instance().sound();

    sound.load_music_collection(m_id_1,
                                { "/assets/music/music_1.mp3",
                                  "/assets/music/music_2.mp3",
                                  "/assets/music/music_3.mp3" });

    sound.load_music_collection(m_id_2, { "/assets/music/music_4.mp3" });
}

bool MusicTestScene::handle_input(uil::Context const& context) const {
    auto const keep_handle_input = Scene::handle_input(context);

    for (const auto& [rectangle,func] : m_buttons) {
        auto const col = Rectangle{ rectangle.x * context.resolution.x, rectangle.y * context.resolution.y,
                                    rectangle.width * context.resolution.x, rectangle.height * context.resolution.y };
        if (CheckCollisionPointRec(context.mouse_position, col)) {
            if (uil::AppContext::instance().input().is_pressed(uil::Mouse::MOUSE_BUTTON_LEFT)) {
                print_error(func());
            }
        }
    }

    return keep_handle_input;
}

void MusicTestScene::render(const uil::Context& context) const {
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
        std::cerr << "Invalid number of buttons or labels!\n";
        return;
    }

    for (auto const& [button, label] : std::views::zip(m_buttons, labels)) {
        auto const rect = button.first;
        auto const col  = Rectangle{ rect.x * context.resolution.x, rect.y * context.resolution.y,
                                    rect.width * context.resolution.x, rect.height * context.resolution.y };

        DrawRectangleLinesEx(col, 1.0f, WHITE);
        DrawText(label, static_cast<int>(col.x), static_cast<int>(col.y), 30,WHITE);
    }
}
