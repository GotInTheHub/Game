#include "mouse.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    void Mouse::press(MouseButton b)
    {
        size_t i = (size_t)b;

        if (!m_current[i])
            m_pressed[i] = true;

        m_current[i] = true;
    }

    void Mouse::release(MouseButton b)
    {
        m_current[(size_t)b] = false;
    }

    void Mouse::setPosition(float x, float y)
    {
        m_pos = { x, y };
    }

    void Mouse::update()
    {
        m_delta = { m_pos.x - m_last.x, m_pos.y - m_last.y };
        m_last = m_pos;

        m_pressed.fill(false);
    }

    bool Mouse::isDown(MouseButton b) const
    {
        return m_current[(size_t)b];
    }

    bool Mouse::isPressed(MouseButton b) const
    {
        return m_pressed[(size_t)b];
    }

    glm::vec2 Mouse::position() const { return m_pos; }
    glm::vec2 Mouse::delta() const { return m_delta; }
}