#pragma once

struct GLFWwindow;

#include "../Input/input_system.hpp"

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

        InputSystem& input();

    private:
        void initCallbacks();

        GLFWwindow* m_window;
        InputSystem m_input;
    };
}