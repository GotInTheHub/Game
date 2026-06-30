#include "mouse.hpp"

namespace Engine
{
    Mouse::Mouse()
    {
        m_buttons.fill(ButtonState::Up);
    }

    void Mouse::press(MouseButton button)
    {
        auto& state = m_buttons[static_cast<size_t>(button)];

        if (state == ButtonState::Up || state == ButtonState::Released)
            state = ButtonState::Pressed;
    }

    void Mouse::release(MouseButton button)
    {
        m_buttons[static_cast<size_t>(button)] = ButtonState::Released;
    }

    void Mouse::setPosition(float x, float y)
    {
        m_delta = { x - m_position.x, y - m_position.y };
        m_position = { x, y };
    }

    void Mouse::setDelta(float dx, float dy)
    {
        m_delta = { dx, dy };
    }

    void Mouse::update()
    {
        for (auto& state : m_buttons)
        {
            if (state == ButtonState::Pressed)
                state = ButtonState::Down;

            else if (state == ButtonState::Released)
                state = ButtonState::Up;
        }

        m_delta = { 0.0f, 0.0f };
    }

    bool Mouse::isDown(MouseButton button) const
    {
        auto state = m_buttons[static_cast<size_t>(button)];
        return state == ButtonState::Down || state == ButtonState::Pressed;
    }

    bool Mouse::isPressed(MouseButton button) const
    {
        return m_buttons[static_cast<size_t>(button)] == ButtonState::Pressed;
    }

    bool Mouse::isReleased(MouseButton button) const
    {
        return m_buttons[static_cast<size_t>(button)] == ButtonState::Released;
    }

    Vec2 Mouse::position() const
    {
        return m_position;
    }

    Vec2 Mouse::delta() const
    {
        return m_delta;
    }
}