#include "input_system.hpp"

namespace Engine
{
    void InputSystem::update()
    {
        // currently nothing here (GLFW feeds events externally)
    }

    Keyboard& InputSystem::keyboard()
    {
        return m_keyboard;
    }

    Mouse& InputSystem::mouse()
    {
        return m_mouse;
    }

    void InputSystem::endFrame()
    {
        m_keyboard.update();
        m_mouse.update();
    }
}