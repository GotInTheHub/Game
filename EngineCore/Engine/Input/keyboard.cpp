#include "keyboard.hpp"

namespace Engine
{
    void Keyboard::press(Key key)
    {
        size_t i = static_cast<size_t>(key);

        if (!m_down[i])
            m_pressed[i] = true;

        m_down[i] = true;
    }

    void Keyboard::release(Key key)
    {
        m_down[static_cast<size_t>(key)] = false;
    }

    void Keyboard::beginFrame()
    {
        m_pressed.fill(false);
    }

    bool Keyboard::isDown(Key key) const
    {
        return m_down[static_cast<size_t>(key)];
    }

    bool Keyboard::isPressed(Key key) const
    {
        return m_pressed[static_cast<size_t>(key)];
    }
}