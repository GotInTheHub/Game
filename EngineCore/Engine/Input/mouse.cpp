#include "mouse.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    void Mouse::press(MouseButton b)
    {
        size_t i = static_cast<size_t>(b);

        if (!m_down[i])
            m_pressed[i] = true;

        m_down[i] = true;
    }

    void Mouse::release(MouseButton b)
    {
        m_down[static_cast<size_t>(b)] = false;
    }

    void Mouse::setPosition(float x, float y)
    {
        m_pos = { x, y };
    }

    void Mouse::beginFrame()
    {
        m_pressed.fill(false);

        m_delta = {
            m_pos.x - m_last.x,
            m_pos.y - m_last.y
        };

        m_last = m_pos;
    }

    bool Mouse::isDown(MouseButton b) const
    {
        return m_down[static_cast<size_t>(b)];
    }

    bool Mouse::isPressed(MouseButton b) const
    {
        return m_pressed[static_cast<size_t>(b)];
    }

    glm::vec2 Mouse::position() const { return m_pos; }
    glm::vec2 Mouse::delta() const { return m_delta; }
}