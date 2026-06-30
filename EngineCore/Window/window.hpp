#pragma once
#include <GLFW/glfw3.h>
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

		void setInputSystem(InputSystem* input);

    private:
        void initCallbacks();

    private:
        GLFWwindow* m_window = nullptr;
        InputSystem* m_input = nullptr;
    };
}