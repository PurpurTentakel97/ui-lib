//
// Purpur Tentakel
// 07.07.24
//

#pragma once
#include <uil/element.hpp>

namespace uil {
    class Text : public UIElement {
    private:
        float m_relative_font_size;
        float m_font_size;
        std::string m_raw_text{};
        std::string m_aligned_text{};
        Alignment m_text_alignment = Alignment::TopLeft;
        bool m_breaking            = false;
        float m_spacing            = 3.0f;
        Color m_color              = WHITE;
        Font const* m_font         = nullptr;

        void update_();
        void align();
        void break_();

    public:
        Callback<Text&> on_text_size_changed{};
        Callback<Text&> on_text_changed{};
        Callback<Text&> on_spacing_changed{};
        Callback<Text&> on_color_changed{};

        Text(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution, float font_size);

        void set_text(std::string text);
        [[nodiscard]] std::string text() const;

        void set_relative_font_size(float size);
        [[nodiscard]] float relative_font_size() const;

        void set_absolute_font_size(float size);
        [[nodiscard]] float absolute_font_size() const;

        void set_spacing(float spacing);
        [[nodiscard]] float spacing() const;

        void set_color(Color color);
        [[nodiscard]] Color color() const;

        void set_text_alignment(Alignment alignment);
        [[nodiscard]] Alignment text_alignment() const;

        void set_breaking(bool breaking);
        [[nodiscard]] bool breaking() const;

        [[nodiscard]] bool check(Context const& context) override;
        [[nodiscard]] bool render(Context const& context) const override;
        void resize(Context const& context) override;
    };
} // namespace uil
