#include "renderer.h"
#include <iostream>
#include "../Debug/Logger/logger.h"

namespace Engine
{
	Renderer::Renderer() : m_window(nullptr), m_initialized(false) {}

	Renderer::~Renderer() {
		shutdown();
	}

	bool Renderer::initialize(EngineContext& context)
	{
		Logger& logger = context.get<Logger>();

		if (m_initialized) {
			logger.log(LogLevel::WARNING, LogCategory::RENDER, "Renderer already initialized");
			return false;
		}

		Window* window = context.tryGet<Window>();

		if (window == nullptr) {
			logger.log(LogLevel::ERROR, LogCategory::RENDER, "Renderer initialization failed: Window system not found in context");
			return false;
		}

		m_window = window;

		// Make this window's GL context current before touching any
		// GL/GLAD calls below.
		glfwMakeContextCurrent(window->nativeHandler());

		// Initialize graphics context (loads GLAD)
		if (!m_graphicsContext.initialize((GLADloadproc)glfwGetProcAddress)) {
			logger.log(LogLevel::ERROR, LogCategory::RENDER, "Renderer initialization failed: Graphics context initialization failed");
			return false;
		}

		// Set default GL state
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		m_initialized = true;
		logger.log(LogLevel::INFO, LogCategory::RENDER, "Renderer initialized successfully");

		return true;
	}

	void Renderer::shutdown() {
		if (m_initialized)
		{
			m_graphicsContext.shutdown();
			m_window = nullptr;
			m_initialized = false;
		}
	}

	void Renderer::update(float dt)
	{
	}

	void Renderer::beginFrame() {
		if (!m_initialized) return;
	}

	void Renderer::endFrame() {
		if (!m_initialized) return;
		glfwSwapBuffers(m_window->nativeHandler());
	}

	void Renderer::clear(float r, float g, float b, float a) {
		if (!m_initialized) return;
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};