#pragma once
#include "graphics_context.h"
#include "../Core/engine_context.h"
#include "../Core/engine_config.h"
#include "../Core/engine_system.h"
#include "../Window/window.h"

struct GLFWwindow;

namespace Engine {
	class Renderer : public IEngineSystem {
	private:
		GraphicsContext m_graphicsContext;
		Window* m_window;
		bool m_initialized;

	public:
		Renderer();
		~Renderer();
		
		// IEngineSystem interface
		bool initialize(EngineContext& context) override;
		void shutdown() override;
		void update(float dt) override;

		// Frame management
		void beginFrame();
		void endFrame();
		void beginFrame(float r, float g, float b, float a) {
			beginFrame();
			clear(r, g, b, a);
		}

		// Clear the screen
		void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

		// Check if initialized
		bool isInitialized() const { return m_initialized; }

		// Get graphics context
		GraphicsContext& getGraphicsContext() { return m_graphicsContext; }
	};
}