//
// Created by marti on 19.06.2025.
//

#include "button_test_scene.hpp"
#include <cpt/log.hpp>
#include <uil/elements/button.hpp>
#include <uil/global/app_context.hpp>

uil::ButtonAssetConfig ButtonTestScene::gen_button_asset_config() {
    auto assets = uil::ButtonAssetConfig{};
    auto& sound = uil::AppContext::instance().sound();

    if (auto const result = sound.load_sound("/assets/sounds/clicked_accepted_std.mp3"); result.has_value()) {
        assets.clicked_sound_id = result.value();
    }

    if (auto const result = sound.load_sound("/assets/sounds/clicked_disabled_std.mp3"); result.has_value()) {
        assets.disabled_sound_id = result.value();
    }

    if (auto const result = sound.load_sound("/assets/sounds/clicked_press_std.mp3"); result.has_value()) {
        assets.pressed_sound_id = result.value();
    }

    if (auto const result = sound.load_sound("/assets/sounds/clicked_release_std.mp3"); result.has_value()) {
        assets.released_sound_id = result.value();
    }

    if (auto const result = sound.load_sound("/assets/sounds/hovered_std.mp3"); result.has_value()) {
        assets.hovered_off_sound_id = result.value();
        assets.hovered_on_sound_id  = result.value();
    }

    return assets;
}

ButtonTestScene::ButtonTestScene() {
    // buttons
    m_button_1          = emplace_top<uil::Button>(Rectangle{ 0.5f, 0.5f, 0.2f, 0.1f }, uil::Alignment::MidMid);
    auto const locked_1 = m_button_1.lock();
    locked_1->on_clicked += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_clicked"); };
    locked_1->on_pressed += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_pressed"); };
    locked_1->on_released += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_released"); };
    locked_1->on_enabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_enabled"); };
    locked_1->on_disabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_disabled"); };
    m_button_2          = emplace_top<uil::Button>(Rectangle{ 0.5f, 0.7f, 0.2f, 0.1f }, uil::Alignment::MidMid);
    auto const locked_2 = m_button_2.lock();
    locked_2->on_clicked += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_clicked"); };
    locked_2->on_pressed += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_pressed"); };
    locked_2->on_released += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_released"); };
    locked_2->on_enabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_enabled"); };
    locked_2->on_disabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_disabled"); };
    locked_2->disable();

    // focus
    auto config_1     = uil::FocusConfig{};
    config_1.down     = m_button_2;
    config_1.next     = m_button_2;
    config_1.previous = m_button_2;
    locked_1->set_focus_config(config_1);

    auto config_2     = uil::FocusConfig{};
    config_2.down     = m_button_1;
    config_2.next     = m_button_1;
    config_2.previous = m_button_1;
    locked_2->set_focus_config(config_2);

    uil::AppContext::instance().focus().set_current(m_button_1);

    // assets
    auto const assets = gen_button_asset_config();
    locked_1->set_asset_config(assets);
    locked_2->set_asset_config(assets);
}
