#include "window.hpp"

#include <GLFW/glfw3.h>

namespace Engine
{
    static void keyCallback(GLFWwindow* window, int key, int, int action, int)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!self) return;

        auto& kb = self->input().keyboard();

        if (action == GLFW_PRESS)
            kb.press(static_cast<Key>(key));   // simplified mapping

        else if (action == GLFW_RELEASE)
            kb.release(static_cast<Key>(key));
    }

    Window::Window(int width, int height, const char* title)
    {
        glfwInit();
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        glfwSetWindowUserPointer(m_window, this);

        initCallbacks();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::initCallbacks()
    {
        glfwSetKeyCallback(m_window, keyCallback);
    }

    void Window::swapBuffers()
    {
		glfwSwapBuffers(m_window);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    InputSystem& Window::input()
    {
        return m_input;
    }
}