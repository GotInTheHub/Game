#pragma once

#include <array>

namespace Engine
{
    enum class MouseButton
    {
        Left,
        Right,
        Middle,
        Button4,
        Button5,

        Count
    };

    struct Vec2
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    enum class ButtonState
    {
        Up,
        Pressed,
        Down,
        Released
    };

    class Mouse
    {
    public:
        Mouse();

        // Called by engine (Window layer)
        void press(MouseButton button);
        void release(MouseButton button);

        void setPosition(float x, float y);
        void setDelta(float dx, float dy);

        // Called once per frame
        void update();

        // Queries
        bool isDown(MouseButton button) const;
        bool isPressed(MouseButton button) const;
        bool isReleased(MouseButton button) const;

        Vec2 position() const;
        Vec2 delta() const;

    private:
        std::array<ButtonState, static_cast<size_t>(MouseButton::Count)> m_buttons;

        Vec2 m_position;
        Vec2 m_delta;
    };
}