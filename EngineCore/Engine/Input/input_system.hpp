#pragma once

#include "keyboard.hpp"
#include "mouse.hpp"

namespace Engine
{
    class InputSystem
    {
    public:
        void beginFrame();

        Keyboard& keyboard();
        Mouse& mouse();

    private:
        Keyboard m_keyboard;
        Mouse m_mouse;
    };
}