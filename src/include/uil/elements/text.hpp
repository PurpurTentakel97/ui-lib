//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include <string>
#include <uil/debug/debug_wrapper.hpp>
#include <uil/element.hpp>
#include <utility>
#include <vector>

namespace uil {

    /**
     * Displays a string inside a collider.
     * use the set-member-functions to configure.
     */
    class Text : public UIElement {
    private:
        using DrawText = std::vector<std::pair<Rectangle, std::string>>;
        std::string m_raw_text{};
        DrawText m_draw_text{};
        Alignment m_text_alignment         = Alignment::TopLeft;
        bool m_breaking                    = false;
        float m_relative_font_size         = 0.015f;
        float m_relative_letter_spacing    = 0.001f;
        float m_relative_line_spacing      = 0.001f;
        float m_relative_paragraph_spacing = 0.01f;
        Color m_color                      = WHITE;
        Font const* m_font                 = nullptr;
        float m_font_size;
        float m_letter_spacing;
        float m_line_spacing;
        float m_paragraph_spacing;

        void align();
        void break_();

    protected:
        /**
         * renders the actual text
         *
         * the text must be updated with the update_text() function
         *
         * @param context all changes of the last frame
         * @param color text color
         */
        void render_text(UpdateContext const& context, Color color) const;
        /**
         *
         * @return a vector of strings and absolute offsets in pixels
         */
        [[nodiscard]] DrawText draw_text() const;
        /**
         *
         * @return absolute font size in pixels
         */
        [[nodiscard]] float absolute_font_size() const;
        /**
         *
         * @return absolute letter spacing in pixels
         */
        [[nodiscard]] float absolute_letter_spacing() const;
        /**
         *
         * @return absolute line spacing in pixels
         */
        [[nodiscard]] float absolute_line_spacing() const;
        /**
         *
         * @return absolute paragraph spacing in pixels
         */
        [[nodiscard]] float absolute_paragraph_spacing() const;


    public:
        debug::TextDebug debug_text{};

        // clang-format off
        Callback<Text&, float, float>                           on_text_size_changed{};         ///< contains Text, new value, old value
        Callback<Text&, std::string const&, std::string const&> on_text_changed{};              ///< contains Text, new value, old value
        Callback<Text&, float, float>                           on_letter_spacing_changed{};    ///< contains Text, new value, old value
        Callback<Text&, Color, Color>                           on_color_changed{};             ///< contains Text, new value, old value
        Callback<Text&, float, float>                           on_line_spacing_chanced{};      ///< contains Text, new value, old value
        Callback<Text&, float, float>                           on_paragraph_spacing_chanced{}; ///< contains Text, new value, old value
        Callback<Text&, Alignment, Alignment>                   on_text_alignment_chanced{};    ///< contains Text, new value, old value
        Callback<Text&, bool, bool>                             on_breaking_chanced{};          ///< contains Text, new value, old value
        Callback<Text&>                                         on_draw_text_updated{};         ///< contains Text
        // clang-format on

        /**
         *
         * @param resolution current resolution
         * @param relative relative position and size of the Element
         * @param alignment alignment for the relative position
         */
        Text(cpt::Vec2_i resolution, Rectangle relative, Alignment alignment);

        /**
         *
         * @param text gets displayed
         */
        void set_text(std::string text);
        /**
         *
         * @return currently displayed text
         */
        [[nodiscard]] std::string text() const;

        /**
         *
         * @param size relative font size
         */
        void set_font_size(float size);
        /**
         *
         * @return relative font size
         */
        [[nodiscard]] float font_size() const;

        /**
         *
         * @param spacing relative letter spacing
         */
        void set_letter_spacing(float spacing);
        /**
         *
         * @return relative letter spacing
         */
        [[nodiscard]] float letter_spacing() const;

        /**
         *
         * @param spacing relative line spacing
         */
        void set_line_spacing(float spacing);
        /**
         *
         * @return relative line spacing
         */
        [[nodiscard]] float line_spacing() const;

        /**
         *
         * @param spacing relative paragraph spacing
         */
        void set_paragraph_spacing(float spacing);
        /**
         *
         * @return relative paragraph spacing
         */
        [[nodiscard]] float paragraph_spacing() const;

        /**
         *
         * @param color text color
         */
        void set_color(Color color);
        /**
         *
         * @return text color
         */
        [[nodiscard]] Color color() const;

        /**
         *
         * @param alignment alignment of the displayed text inside the collider
         */
        void set_text_alignment(Alignment alignment);
        /**
         *
         * @return alignment of the displayed text inside the collider
         */
        [[nodiscard]] Alignment text_alignment() const;

        /**
         *
         * @param breaking defines whether the text gets transformed into a multiline text
         */
        void set_breaking(bool breaking);
        /**
         *
         * @return whether the text gets transformed into a multiline text
         */
        [[nodiscard]] bool breaking() const;

        /**
         * breaks and aligns the text when it was configuration that way
         */
        void update_text();

        /**
         * gets the current font and calls to update
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep checking or not
         */
        [[nodiscard]] bool handle_input(UpdateContext const& context) override;
        /**
         * in debug build: renders line collider
         *
         * @param context all changes of the last frame
         */
        void render(UpdateContext const& context) const override;
        /**
         * updated all absolute values and the UIElement
         *
         * @param context all changes of the last frame
         */
        void resize(UpdateContext const& context) override;
    };
} // namespace uil
