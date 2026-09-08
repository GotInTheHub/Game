#include "engine.h"

namespace Engine
{
    Engine::Engine()
    { }

    bool Engine::initialize(const EngineConfig& config)
    {
        m_window = std::make_unique<Window>(
            config.width,
            config.height,
            config.title.c_str()
        );
        m_window->setInputSystem(&m_input);

        // Register every system once, up front. From here on, adding a new
        // system is: add the member, add one provide<>() line, add it to
        // m_systems - nothing else in this function changes.
		m_context.provide<Window>(m_window.get());
		m_context.provide<InputSystem>(&m_input);
		m_context.provide<Logger>(&m_logger);
		m_context.provide<Console>(&m_console);
		m_context.provide<Renderer>(&m_renderer);

#ifdef _DEBUG
		m_logger.setMinLogLevel(LogLevel::DEBUG);
#endif

        m_systems = { &m_logger, &m_console, &m_renderer };

		for (IEngineSystem* system : m_systems)
		{
			if (!system->initialize(m_context))
			{
				return false;
			}
		}

		return true;
    }

    void Engine::update(float dt)
    {
		for (IEngineSystem* system : m_systems)
		{
			system->update(dt);
		}
    }

    void Engine::beginFrame()
    {
        m_window->pollEvents();
    }

    void Engine::endFrame()
    {
        // CRITICAL:
        // reset per-frame input states AFTER game logic
        m_input.beginFrame();

        m_window->swapBuffers();
    }

    bool Engine::isRunning() const
    {
        return !m_window->shouldClose();
    }

    void Engine::shutdown()
    {
		// Shut down in reverse order of initialization, to avoid dangling dependencies.
		for (auto it = m_systems.rbegin(); it != m_systems.rend(); ++it)
		{
			(*it)->shutdown();
		}

        m_window->close();
    }

    Window& Engine::window()
    {
        return *m_window;
    }

    InputSystem& Engine::input()
    {
        return m_input;
    }
    Logger& Engine::logger()
    {
        return m_logger;
    }
    Console& Engine::console()
    {
		return m_console;
    }
    Renderer& Engine::renderer()
    {
		return m_renderer;
    }
    EngineContext& Engine::context()
    {
		return m_context;
    }
}