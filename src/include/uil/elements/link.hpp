//
// Purpur Tentakel
// 27.07.24
//

#pragma once
#include <uil/elements/text.hpp>

/*
 * Provides a clickable Link
 */
namespace uil {
    class Link : public Text {
    private:
        bool m_clicked        = false;
        bool m_render_hover   = true;
        Color m_color_clicked = PURPLE;
        std::string m_link{};

    public:
        using Text::Text;

        /*
         * @param[in] color the link turns to when it was clicked
         */
        void set_color_clicked(Color color);
        /*
         * @returns current color the link turns to whens it was clicked
         */
        [[nodiscard]] Color color_clicked() const;

        /*
         * @param[in] string that gets called when the link is clickd
         * @see string will not be validated
         */
        void set_link(std::string link);
        /*
         * @returns current string that gets called when the links is clicked.
         */
        [[nodiscard]] std::string link() const;

        /*
         * @param[in] if the link was clicked.
         * @see this will change the link color
         */
        void set_clicked(bool clicked);
        /*
         * @returns if the link was clicked.
         */
        [[nodiscard]] bool clicked() const;

        /*
         * @param[in] if the link gets underlined when hovering.
         */
        void set_render_hover(bool render_hover);
        /*
         * @returns if the links gets currently unterlind when hovering.
         */
        [[nodiscard]] bool render_hover() const;

        /*
         * calls Text to check
         * calls Link when collider is hovered and left mouse button is clicked
         * chances cursor to poiting finger when hovered
         *
         *
         * @param[in] contains the context of all changes
         * @return default: return value from Text::check()
         * @return false when hovered or clicked
         */
        [[nodiscard]] bool check(Context const& context) override;
        /*
         * calls UIElement to render
         * calls render_text() in Text
         * render hover when activated
         *
         * @param[in] contains the context of all changes
         * @return return value from UIElement::render()
         */
        [[nodiscard]] bool render(Context const& context) const override;
    };
} // namespace uil
