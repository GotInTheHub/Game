#include "keyboard.hpp"

namespace Engine
{
    void Keyboard::press(Key key)
    {
        size_t i = (size_t)key;

        if (!m_current[i])
            m_pressed[i] = true;

        m_current[i] = true;
    }

    void Keyboard::release(Key key)
    {
        m_current[(size_t)key] = false;
    }

    void Keyboard::update()
    {
        m_pressed.fill(false);
    }

    bool Keyboard::isDown(Key key) const
    {
        return m_current[(size_t)key];
    }

    bool Keyboard::isPressed(Key key) const
    {
        return m_pressed[(size_t)key];
    }
}