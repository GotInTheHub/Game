#include "application.h"

namespace Game
{
    Application::Application()
    {
		Engine::EngineConfig config;
		config.width = 1280;
		config.height = 720;
		config.title = "Game";
		if (!m_engine.initialize(config))
		{
			throw std::runtime_error("Failed to initialize engine");
		}
		m_game.initialize(m_engine);
    }

    void Application::run()
    {
		auto lastTime = std::chrono::steady_clock::now();

        while (m_engine.isRunning())
        {
			auto now = std::chrono::steady_clock::now();
			float dt = std::chrono::duration<float>(now - lastTime).count();
			lastTime = now;

            m_engine.beginFrame();

			m_engine.update(dt);
			m_game.update(m_engine);
            m_game.render(m_engine);

            m_engine.endFrame();
        }

        m_game.shutdown();

		m_engine.shutdown();
    }
}