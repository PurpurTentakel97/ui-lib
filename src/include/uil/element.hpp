//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <raylib.h>
#include <uil/alignment.hpp>
#include <uil/base_element.hpp>
#include <uil/callback.hpp>
#include <uil/helper/rect.hpp>

namespace uil {
    struct Context;

    /**
    * the basic element for all things that gets displayed into a scene.
    * override this for own elements.
    * make sure to call check, update, render, and resize of UIElement when you override it.
    */
    class UIElement : public BaseElement {
    private:
        enum class MoveType {
            None,
            Linear_Time,  // moves linear to a certain point in a certain time
            Linear_Speed, // moves linear to a certain point in a certain speed
            Slow_To_Fast, // getting faster while moving to a certain point
            Fast_To_Slow, // getting slower while moving to a certain point
            Constant,     // moves at a constant speed until it gets stoppt manualy
        };

        // basic
        cpt::Vec2_i m_resolution;
        Alignment m_alignment;
        Rectangle m_relative{}; // m_relative needs to be initialized bevor m_collider
        Rectangle m_collider{}; // m_relative needs to be initialized bevor m_collider
        bool m_render_collider = false;
        bool m_hovered         = false;

        // movement
        MoveType m_move_type      = MoveType::None;
        MoveType m_last_move_type = MoveType::None;
        float m_move_speed{};
        float m_move_time{};
        Vector2 m_relative_origin{};
        Vector2 m_relative_destination{};
        Vector2 m_move_direction{};

        void update_relative();
        void update_collider();

        [[nodiscard]] bool is_arriving(Vector2 const& distance) const;
        void arriving();

        void move(Vector2 const& relative_distance);
        void linear_time(float delta_time);
        void linear_speed(float delta_time);
        void linear(Vector2 const& direction);
        void fast_to_slow(float delta_time);
        void slow_to_fast(float delta_time);
        void constant(float delta_time);


    protected:
        /**
         *
         * @return last resolution that was captured by last resize
         */
        [[nodiscard]] cpt::Vec2_i resolution() const;

    public:
        Callback<UIElement&> on_movement_start{}; ///< contains UIElement
        Callback<UIElement&> on_movement_stop{};  ///< contains UIElement
        Callback<UIElement&> on_arrived{};        ///< contains UIElement
        Callback<UIElement&> on_check{};          ///< contains UIElement
        Callback<UIElement&> on_update{};         ///< contains UIElement
        Callback<UIElement const&> on_draw{};     ///< contains UIElement
        Callback<UIElement&> on_resize{};         ///< contains UIElement

        /**
         * aligns the relative position acording to the provided alignment.
         * calculates the absolute collider out of the relative position and size and the resolution.
         *
         * @param resolution current resolution for absolute position and size
         * @param relative relative position and size of the collider
         * @param alignment moves the relative position
         */
        UIElement(cpt::Vec2_i resolution, Rectangle relative, Alignment alignment);

        UIElement(UIElement const&)            = delete; ///< no need because handle with unique_ptr
        UIElement(UIElement&&)                 = delete; ///< no need because handle with unique_ptr
        UIElement& operator=(UIElement const&) = delete; ///< no need because handle with unique_ptr
        UIElement& operator=(UIElement&&)      = delete; ///< no need because handle with unique_ptr
        /**
         * just for polimorphism.
         */
        virtual ~UIElement()                   = default;

        // basic
        /**
         * alignes the provided position and updates the absolute collider.
         *
         * @param position unaligned relative positon
         */
        void set_relative_position(Vector2 position);
        /**
         * reverses the aligment with old size and aligns with new size.
         * updates absolute collider.
         *
         * @param size relative size
         */
        void set_relative_size(Vector2 size);
        /**
         * updates absolute collider.
         *
         * @param relative relative position and size
         */
        void set_relative(Rectangle relative);
        /**
         * returns the relative unaligned (provided) position and size.
         *
         * @return relative position and size
         */
        [[nodiscard]] Rectangle relative() const;
        /**
         * returns the relative aligned position and size.
         * this will always be the top left corner if the element.
         *
         * @return aligned relative position and size
         */
        [[nodiscard]] Rectangle relative_aligned() const;

        /**
         * aligns the absolute position.
         * update relative values.
         *
         * @param position absolute position
         */
        void set_absolute_position(Vector2 position);
        /**
         * reverses alignment with old size and aligns with new size.
         * updates relative values.
         *
         * @param size absolute size
         */
        void set_absolute_size(Vector2 size);
        /**
         * updates relative values.
         *
         * @param collider absolute position and size.
         */
        void set_collider(Rectangle collider);
        /**
         * returns the absolute unaligned (provided) position and size.
         *
         * @return unaligned absolute position and size
         */
        [[nodiscard]] Rectangle collider() const;
        /**
         * returns the aligned absolute position and size.
         * this will always be the top left coner of the element.
         *
         * @return aligned absolute position and size
         */
        [[nodiscard]] Rectangle collider_aligned() const;

        /**
         * revesed the alignment with the old alignment and aligns with new alignment.
         *
         * @param alignment alignment for element
         */
        void set_alignment(Alignment alignment);
        /**
         *
         * @return current alignment
         */
        [[nodiscard]] Alignment alignment() const;

        /**
         * this will only render in debug mode.
         *
         * @param render defines if the collider gets renderd
         */
        void set_render_collider_debug(bool render);
        /**
         *
         * @return if collider gets currently rendered
         */
        [[nodiscard]] bool render_collider_debug() const;

        /**
         *
         * @return if element is currently hovered
         */
        [[nodiscard]] bool hovered() const;

        // movement
        /**
         *
         * @return if element is currently moving
         */
        [[nodiscard]] bool is_moving() const;
        /**
         * will move the element to a certain relative position within a provided time.
         * this movement is linear.
         * this movement will stop when arrived.
         *
         * @param destination relative point the element will move to
         * @param time time in s
         */
        void move_to_linear_time(Vector2 destination, float time);
        /**
         * will move the element to a certain relative position with a provided speed.
         * this movement is linear.
         * this movement will stop when arrived.
         *
         * @param destination relative point the element will move to
         * @param speed speed the element will move with
         */
        void move_to_linear_speed(Vector2 destination, float speed);
        /**
         * will move the element to a certain relative position with a provided speed.
         * this movement starts fast and slows down.
         * this movement will stop when arrived.
         *
         * @param destination relative point the element will move to
         * @param speed speed the element will move with
         */
        void move_to_fast_to_slow(Vector2 destination, float speed);
        /**
         * will move the element to a certain relative position with a provided speed.
         * this movement starts slow and speeds up.
         * this movement will stop when arrived.
         *
         * @param destination relative point the element will move to
         * @param speed speed the element will move with
         */
        void move_to_slow_to_fast(Vector2 destination, float speed);
        /**
         * will move the element with a provided speed.
         * this movement is linear.
         * this movement will not stop. it has to be stopped with move_stop().
         *
         * @param direction direction the element is moving
         * @param speed speed the element will move with
         */
        void move_constant(Vector2 direction, float speed);
        /**
         * stops all movement of the element immediately.
         */
        void move_stop();

        /**
         *
         * @return if the element started moving in this frame
         */
        [[nodiscard]] bool has_started_moving() const;
        /**
         *
         * @return if the element stopped moving in this frame
         */
        [[nodiscard]] bool has_stopped_moving() const;

        // polymorphic
        /**
         * stores the current movetype.
         * checks if element is hovered.
         *
         * override this when the derived element has to check additional stuff.
         * make shure to call UIElement::check().
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep checking
         */
        [[nodiscard]] virtual bool handle_input(Context const& context);
        /**
         * updates current movement if element is moving.
         *
         * override this when the derived element has to update additional stuff.
         * make shure to call UIElement::update().
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep updating
         */
        [[nodiscard]] virtual bool update(Context const& context);
        /**
         * renders collider if cofigured.
         * this only works in debug build.
         *
         * override this when the derived element has to render additional stuff.
         * make shure to call UIElement::render().
         *
         * @param context all changes of the last frame
         * @throw uil::BadMovementType unexpected movement enum. mostly happens when the enum has an non predefinded value.
         */
        virtual void render(Context const& context) const;
        /**
         * updates resolution and collider.
         *
         * override this when the derived element has to resize additional stuff.
         * make shure to call UIElement::resize().
         *
         * @param context all changes of the last frame
         */
        virtual void resize(Context const& context);
    };
} // namespace uil
