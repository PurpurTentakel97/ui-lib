//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include <string>
#include <uil/element.hpp>
#include <utility>
#include <vector>

namespace uil {
    class Text : public UIElement {
    private:
        using DrawText = std::vector<std::pair<Vector2, std::string>>;
        std::string m_raw_text{};
        DrawText m_draw_text{};
        Alignment m_text_alignment         = Alignment::TopLeft;
        bool m_breaking                    = false;
        bool m_render_line_collider        = false;
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
        void render_text(Context const& context, Color color) const;
        [[nodiscard]] DrawText draw_text() const;
        [[nodiscard]] float absolute_font_size() const;
        [[nodiscard]] float absolute_letter_spacing() const;
        [[nodiscard]] float absolute_line_spacing() const;
        [[nodiscard]] float absolute_paragraph_spacing() const;


    public:
        Callback<Text&, float, float> on_text_size_changed{};
        Callback<Text&, std::string const&, std::string const&> on_text_changed{};
        Callback<Text&, float, float> on_letter_spacing_changed{};
        Callback<Text&, Color, Color> on_color_changed{};
        Callback<Text&, float, float> on_line_spacing_chanced{};
        Callback<Text&, float, float> on_paragraph_spacing_chanced{};
        Callback<Text&, Alignment, Alignment> on_text_alignment_chanced{};
        Callback<Text&, bool, bool> on_breaking_chanced{};
        Callback<Text&> on_draw_text_updated{};

        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution);

        void set_text(std::string text);
        [[nodiscard]] std::string text() const;

        void set_font_size(float size);
        [[nodiscard]] float font_size() const;

        void set_letter_spacing(float spacing);
        [[nodiscard]] float letter_spacing() const;

        void set_line_spacing(float spacing);
        [[nodiscard]] float line_spacing() const;

        void set_paragraph_spacing(float spacing);
        [[nodiscard]] float paragraph_spacing() const;

        void set_color(Color color);
        [[nodiscard]] Color color() const;

        void set_text_alignment(Alignment alignment);
        [[nodiscard]] Alignment text_alignment() const;

        void set_breaking(bool breaking);
        [[nodiscard]] bool breaking() const;

        void set_render_line_collider_debug(bool draw);
        [[nodiscard]] bool render_line_collider_debug() const;

        void update_text();

        [[nodiscard]] bool check(Context const& context) override;
        [[nodiscard]] bool render(Context const& context) const override;
        void resize(Context const& context) override;
    };
} // namespace uil
