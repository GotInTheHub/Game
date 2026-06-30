#pragma once

#include "../Input/keyboard.hpp"
#include "../Input/mouse.hpp"

struct GLFWwindow;

namespace Engine
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void pollEvents();
        void swapBuffers();

        bool shouldClose() const;

        Keyboard& keyboard();
        Mouse& mouse();

    private:
        void initCallbacks();

    private:
        GLFWwindow* m_window;

        Keyboard m_keyboard;
        Mouse m_mouse;
    };
}