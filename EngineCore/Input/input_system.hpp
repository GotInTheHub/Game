#pragma once

#include "keyboard.hpp"
#include "mouse.hpp"

namespace Engine
{
    class InputSystem
    {
    public:
        void update();

        Keyboard& keyboard();
        Mouse& mouse();

        void endFrame();

    private:
        Keyboard m_keyboard;
        Mouse m_mouse;
    };
}