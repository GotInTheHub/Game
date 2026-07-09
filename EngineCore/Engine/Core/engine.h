#pragma once

#include <memory>
#include <vector>

#include "../Window/window.h"
#include "../Input/input_system.hpp"
#include "../Debug/Console/console.h"
#include "../Debug/Logger/logger.h"
#include "../Graphics/renderer.h"
#include "engine_context.h"
#include "engine_config.h"
#include "engine_system.h"

namespace Engine
{
    class Engine
    {
    public:
        Engine();
		~Engine() = default;

		bool initialize(const EngineConfig& config);
        void shutdown();

		void update(float dt);
        void beginFrame();
        void endFrame();

        bool isRunning() const;

        Window& window();
		InputSystem& input();
		Logger& logger();
		Console& console();
		Renderer& renderer();

		EngineContext& context();

    private:
		std::unique_ptr<Window> m_window;

		Logger m_logger;
		InputSystem m_input;
		Console m_console;
		Renderer m_renderer;

		EngineContext m_context;

		// Drives initialize/update/shutdown uniformly instead of each
		// system being wired up by hand in a different way. Order here IS
		// execution order: Logger first (so everyone else can log during
		// their own init), Renderer last (needs Window, already registered
		// in m_context by the time this list runs).
		std::vector<IEngineSystem*> m_systems;
    };
}