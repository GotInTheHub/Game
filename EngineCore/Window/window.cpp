#include "window.hpp"
#include "key_translate.hpp"

#include <GLFW/glfw3.h>

namespace Engine
{
    static void keyCallback(GLFWwindow* w, int key, int, int action, int)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

        if (!self) return;

        if (action == GLFW_PRESS)
            self->keyboard().press(translateKey(key));

        else if (action == GLFW_RELEASE)
            self->keyboard().release(translateKey(key));
    }

    static void mouseButtonCallback(GLFWwindow* w, int button, int action, int)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

        if (!self) return;

        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (action == GLFW_PRESS)
                self->mouse().press(MouseButton::Left);
            else
                self->mouse().release(MouseButton::Left);
        }
    }

    static void cursorCallback(GLFWwindow* w, double x, double y)
    {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));

        if (!self) return;

        self->mouse().setPosition((float)x, (float)y);
    }

    Window::Window(int width, int height, const char* title)
    {
        glfwInit();

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

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
        glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_window, cursorCallback);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    Keyboard& Window::keyboard() { return m_keyboard; }
    Mouse& Window::mouse() { return m_mouse; }
}