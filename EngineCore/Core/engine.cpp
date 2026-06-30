#include "engine.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
    Engine::Engine(int width, int height, const char* title)
        : m_window(width, height, title)
    {}

    void Engine::beginFrame()
    {
        m_window.pollEvents();
    }

    void Engine::endFrame()
    {
        m_window.keyboard().update();
        m_window.mouse().update();

        m_window.swapBuffers();
    }

    bool Engine::isRunning() const
    {
        return !m_window.shouldClose();
    }

    Window& Engine::window()
    {
        return m_window;
    }
}