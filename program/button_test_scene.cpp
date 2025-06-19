//
// Created by marti on 19.06.2025.
//

#include "button_test_scene.hpp"
#include <cpt/log.hpp>
#include <uil/elements/button.hpp>
#include <uil/global/app_context.hpp>

ButtonTestScene::ButtonTestScene() {
    m_button_1          = emplace_top<uil::Button>(Rectangle{ 0.5f, 0.5f, 0.2f, 0.1f }, uil::Alignment::MidMid);
    auto const locked_1 = m_button_1.lock();
    locked_1->on_clicked += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_clicked"); };
    locked_1->on_pressed += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_pressed"); };
    locked_1->on_released += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_released"); };
    locked_1->on_enabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_enabled"); };
    locked_1->on_disabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_disabled"); };
    locked_1->on_hovered += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 1: on_hovered"); };

    m_button_2          = emplace_top<uil::Button>(Rectangle{ 0.5f, 0.7f, 0.2f, 0.1f }, uil::Alignment::MidMid);
    auto const locked_2 = m_button_2.lock();
    locked_2->on_clicked += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_clicked"); };
    locked_2->on_pressed += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_pressed"); };
    locked_2->on_released += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_released"); };
    locked_2->on_enabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_enabled"); };
    locked_2->on_disabled += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_disabled"); };
    locked_2->on_hovered += [](auto const&) { cpt::log::r_info("Button Test Scene: Button 2: on_hovered"); };
    locked_2->disable();

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
}
