//
// Created by marti on 30.05.2025.
//


#include "focus_test_scene.hpp"
#include "uil/global/app_context.hpp"

void Element::render() const {
    UIElement::render();

    DrawRectangleRec(collider_aligned(), RED);

    if (is_focused()) {
        constexpr auto offset = 2.0f;
        DrawRectangleLinesEx({ collider_aligned().x - offset,
                               collider_aligned().y - offset,
                               collider_aligned().width + 2 * offset,
                               collider_aligned().height + 2 * offset },
                             1.0f,
                             WHITE);
    }
}

FocusTestScene::FocusTestScene() {
    auto const gen_single_element = [&](auto const column, auto const row) {
        return emplace_top<Element>(Rectangle{ 0.1f * static_cast<float>(column), 0.1f * static_cast<float>(row), 0.05f, 0.05f }, uil::Alignment::MidMid)
                .lock();
    };

    auto const gen_element_row = [gen_single_element](auto const column_count, auto const row) {
        std::vector<std::shared_ptr<Element>> elements{};
        for (auto i = 0; i < column_count; ++i) {
            elements.push_back(gen_single_element(i + 1, row));
        }
        return elements;
    };

    m_focus_elements.push_back(gen_element_row(4, 1));
    m_focus_elements.push_back(gen_element_row(4, 2));
    m_focus_elements.push_back(gen_element_row(4, 3));
    m_focus_elements.push_back(gen_element_row(4, 4));

    uil::AppContext::instance().focus().set_current(m_focus_elements[0][0]);

    for (std::size_t i = 0; i < m_focus_elements.size(); ++i) {
        for (std::size_t j = 0; j < m_focus_elements[i].size(); ++j) {
            auto const element = m_focus_elements[i][j];

            auto config = uil::FocusConfig{};

            if (j > 0) {
                config.left = m_focus_elements[i][j - 1];
            }
            if (j < m_focus_elements[i].size() - 1) {
                config.right = m_focus_elements[i][j + 1];
            }

            if (i > 0) {
                config.up = m_focus_elements[i - 1][j];
            }
            if (i < m_focus_elements.size() - 1) {
                config.down = m_focus_elements[i + 1][j];
            }

            if (j > 0) {
                config.previous = m_focus_elements[i][j - 1];
            } else if (i > 0) {
                config.previous = m_focus_elements[i - 1][m_focus_elements[i - 1].size() - 1];
            } else {
                config.previous = m_focus_elements[m_focus_elements.size() - 1]
                                                  [m_focus_elements[m_focus_elements.size() - 1].size() - 1];
            }

            if (j < m_focus_elements[i].size() - 1) {
                config.next = m_focus_elements[i][j + 1];
            } else if (i < m_focus_elements.size() - 1) {
                config.next = m_focus_elements[i + 1][0];
            } else {
                config.next = m_focus_elements[0][0];
            }

            element->set_focus_config(config);
        }
    }
}
