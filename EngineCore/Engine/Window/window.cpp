#include "window.h"
#include "key_translate.hpp"
#include <stdexcept>

namespace Engine
{
    Window::Window(int width, int height, const char* title)
    {
        glfwInit();

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}

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
        // KEYBOARD
        glfwSetKeyCallback(m_window,
            [](GLFWwindow* w, int key, int, int action, int)
            {
                auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
                if (!self || !self->m_input) return;

                auto& kb = self->m_input->keyboard();

                Key k = translateKey(key);

                if (action == GLFW_PRESS)
                    kb.press(k);
                else if (action == GLFW_RELEASE)
                    kb.release(k);
            });

        // MOUSE BUTTON
        glfwSetMouseButtonCallback(m_window,
            [](GLFWwindow* w, int button, int action, int)
            {
                auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
                if (!self || !self->m_input) return;

                auto& mouse = self->m_input->mouse();

                MouseButton b =
                    (button == GLFW_MOUSE_BUTTON_LEFT) ? MouseButton::Left :
                    (button == GLFW_MOUSE_BUTTON_RIGHT) ? MouseButton::Right :
                    MouseButton::Middle;

                if (action == GLFW_PRESS)
                    mouse.press(b);
                else
                    mouse.release(b);
            });

        // CURSOR
        glfwSetCursorPosCallback(m_window,
            [](GLFWwindow* w, double x, double y)
            {
                auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
                if (!self || !self->m_input) return;

                self->m_input->mouse().setPosition((float)x, (float)y);
            });
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

    void Window::close()
    {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }

    InputSystem& Window::input()
    {
		return *m_input;
    }

    void Window::setInputSystem(InputSystem* input)
    {
		m_input = input;
    }
}