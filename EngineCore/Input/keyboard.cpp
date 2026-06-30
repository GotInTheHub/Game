#include "keyboard.hpp"

namespace Engine
{
    Keyboard::Keyboard()
    {
        m_states.fill(KeyState::Up);
    }

    void Keyboard::press(Key key)
    {
        auto& state = m_states[static_cast<size_t>(key)];

        if (state == KeyState::Up || state == KeyState::Released)
            state = KeyState::Pressed;
    }

    void Keyboard::release(Key key)
    {
        m_states[static_cast<size_t>(key)] = KeyState::Released;
    }

    void Keyboard::update()
    {
        for (auto& state : m_states)
        {
            if (state == KeyState::Pressed)
                state = KeyState::Down;

            else if (state == KeyState::Released)
                state = KeyState::Up;
        }
    }

    bool Keyboard::isDown(Key key) const
    {
        const auto state = m_states[static_cast<size_t>(key)];
        return state == KeyState::Down || state == KeyState::Pressed;
    }

    bool Keyboard::isPressed(Key key) const
    {
        return m_states[static_cast<size_t>(key)] == KeyState::Pressed;
    }

    bool Keyboard::isReleased(Key key) const
    {
        return m_states[static_cast<size_t>(key)] == KeyState::Released;
    }

    KeyState Keyboard::getState(Key key) const
    {
        return m_states[static_cast<size_t>(key)];
    }
}