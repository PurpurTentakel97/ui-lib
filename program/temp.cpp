//
// Created by marti on 17.05.2024.
//

#include <iostream>
#include <uil/Callback.hpp>


class Button final {
public:
    uil::Callback<Button const&> m_on_click;

    void Check() const {
        m_on_click.invoke(*this);
    }
};

int main() {
    auto btn = Button();

    // v1
    btn.m_on_click += [](Button const& btn) { std::cout << "clicked 1\n"; };
    btn.Check();
    btn.m_on_click += [](Button const& btn) { std::cout << "clicked 2\n"; };
    btn.Check();
    btn.m_on_click.clear();
}
