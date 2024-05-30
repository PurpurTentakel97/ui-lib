//
// Purpur Tentakel
// 30.05.24
//

#pragma once

#include <tl/optional.hpp>
#include <unordered_set>
#include <variant>


namespace uil {
    using InputEvent = std::variant<>;
    using Key        = std::variant</*KeyboardKey, MouseButton, GamepadButton*/>;

    class EventManager final {
    private:
        std::unordered_set<InputEvent> m_events{};
        std::unordered_set<Key> m_keys{};

    public:
        void update();

        tl::optional<InputEvent> next();

        [[nodiscard]] bool is_down(Key key) const;
        [[nodiscard]] bool is_up(Key key) const;
    };
} // namespace uil
