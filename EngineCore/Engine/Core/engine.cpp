#include "engine.hpp"

namespace Engine
{
    Engine::Engine(int width, int height, const char* title)
        : m_window(width, height, title)
    {
		m_window.setInputSystem(&m_input);
    }

    void Engine::beginFrame()
    {
        m_window.pollEvents();
    }

    void Engine::endFrame()
    {
        // CRITICAL:
        // reset per-frame input states AFTER game logic
        m_input.beginFrame();

        m_window.swapBuffers();
    }

    bool Engine::isRunning() const
    {
        return !m_window.shouldClose();
    }

    void Engine::quit()
    {
        m_window.close();
    }

    Window& Engine::window()
    {
        return m_window;
    }

    InputSystem& Engine::input()
    {
        return m_input;
    }
}