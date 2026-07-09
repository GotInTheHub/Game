#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Input/input_system.hpp"

namespace Engine
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

        void pollEvents();
        void swapBuffers();

        bool shouldClose() const;
        void close();

		InputSystem& input();

		void setInputSystem(InputSystem* input);

        // Raw GLFW handle - needed by Renderer for
        // glfwMakeContextCurrent/glfwSwapBuffers. Nothing outside the
        // Engine/Renderer pair should need this.
		GLFWwindow* nativeHandler() const { return m_window; }

    private:
        void initCallbacks();

    private:
        GLFWwindow* m_window = nullptr;
        InputSystem* m_input = nullptr;
    };
}