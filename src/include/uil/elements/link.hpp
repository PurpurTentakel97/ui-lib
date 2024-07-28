//
// Purpur Tentakel
// 27.07.24
//

#pragma once
#include <uil/elements/text.hpp>

namespace uil {
    class Link : public Text {
    private:
        bool m_clicked        = false;
        bool m_render_hover   = true;
        Color m_color_clicked = PURPLE;
        std::string m_link{};

    public:
        using Text::Text;

        void set_color_clicked(Color color);
        [[nodiscard]] Color color_clicked() const;

        void set_link(std::string link);
        [[nodiscard]] std::string link() const;

        void set_clicked(bool clicked);
        [[nodiscard]] bool clicked() const;

        void set_render_hover(bool render_hover);
        [[nodiscard]] bool render_hover() const;

        [[nodiscard]] bool check(Context const& context) override;
        [[nodiscard]] bool render(Context const& context) const override;
    };
} // namespace uil
