//
// Purpur Tentakel
// 27.07.24
//

#pragma once
#include <uil/elements/text.hpp>

/**
 * provides a clickable link
 * use the set-member-functions to configurate
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
        
        /**
         *
         * @param color color the link turns to when it was clicked
         */
        void set_color_clicked(Color color);
        /**
         * 
         * @return color the link turns to when it was clicked
         */
        [[nodiscard]] Color color_clicked() const;

        /**
         * string will not be validated
         *
         * @param link string that gets called when the link is clickd
         */
        void set_link(std::string link);
        /**
         *
         * @return string that gets called when the link is clickd
         */
        [[nodiscard]] std::string link() const;

        /**
         * this sets the clicked status
         *
         * @param clicked if the link was clicked
         */
        void set_clicked(bool clicked);
        /**
         * 
         * @return if the link was clicked
         */
        [[nodiscard]] bool clicked() const;

        /**
         *
         * @param render_hover if the link gets underlined when hovering
         */
        void set_render_hover(bool render_hover);
        /**
         * 
         * @return if the link gets underlined when hovering
         */
        [[nodiscard]] bool render_hover() const;

        /**
         * checks the current state
         *
         * calls text to check.
         * checks whether the text ist hovered or clicked.
         * calls callbacks and link if it so.
         *
         * @param context all changes of the last frameall changes of the last frame
         * @return whether the next scene should keep checking or not
         */
        [[nodiscard]] bool check(Context const& context) override;

        /**
         * renders the current state
         *
         * calls UIEleent to render.
         * calls Text to render text.
         * renders hover when activated.
         * 
         * @param context all changes of the last frameall changes of the last frame
         * @return whether the next scene should keep rendering or not
         */
        [[nodiscard]] bool render(Context const& context) const override;
    };
} // namespace uil
