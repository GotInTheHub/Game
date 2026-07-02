#include "application.hpp"

namespace Engine
{
    Application::Application()
        : m_engine(1280, 720, "Engine")
    {
        m_game.initialize(m_engine);
    }

    void Application::run()
    {
        while (m_engine.isRunning())
        {
            m_engine.beginFrame();

            m_game.update(m_engine);
            m_game.render(m_engine);

            m_engine.endFrame();
        }

        m_game.shutdown();
    }
}