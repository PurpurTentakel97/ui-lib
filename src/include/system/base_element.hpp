//
// Purpur Tentakel
// 07.08.24
//

#pragma once

namespace uil {
    /**
     * Represents a basic element with an active state.
     *
     * This class provides functionality to check and modify the active state
     * of an element, allowing it to be enabled or disabled as necessary.
     */
    class BaseElement {
    private:
        bool m_active = true;

    public:
        /**
         * Checks if the BaseElement is active.
         *
         * @return True if the BaseElement is active; false otherwise.
         */
        [[nodiscard]] bool active() const;
        /**
         * Sets the active state of the BaseElement.
         *
         * @param active The new active state to set. True to activate the BaseElement, false to deactivate it.
         */
        void set_active(bool active);
    };
} // namespace uil
