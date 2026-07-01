#include "input_system.hpp"

namespace Engine
{
    void InputSystem::beginFrame()
    {
        m_keyboard.beginFrame();
        m_mouse.beginFrame();
    }

    Keyboard& InputSystem::keyboard()
    {
        return m_keyboard;
    }

    Mouse& InputSystem::mouse()
    {
        return m_mouse;
    }
}