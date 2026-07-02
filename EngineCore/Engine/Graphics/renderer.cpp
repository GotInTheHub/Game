#include "renderer.h"
#include <iostream>
#include "../Debug/Logger/logger.h"

namespace Engine
{
	Renderer::Renderer() : m_window(nullptr), m_initialized(false) {}

	Renderer::~Renderer() {
		shutdown();
	}

	bool Renderer::initialize(GLFWwindow* window) {
		if (m_initialized) {
			Logger::error(LogCategory::RENDER, "Renderer already initialized");
			return false;
		}

		if (window == nullptr) {
			Logger::error(LogCategory::RENDER, "Window pointer is null");
			return false;
		}

		m_window = window;

		// Make context current
		glfwMakeContextCurrent(m_window);

		// Initialize graphics context (loads GLAD)
		if (!m_graphicsContext.initialize((GLADloadproc)glfwGetProcAddress)) {
			Logger::error(LogCategory::RENDER, "Failed to initialize graphics context");
			return false;
		}

		// Set default GL state
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		m_initialized = true;
		Logger::info(LogCategory::RENDER, "Renderer initialized successfully");

		return true;
	}

	void Renderer::shutdown() {
		if (m_initialized) {
			m_graphicsContext.shutdown();
			m_window = nullptr;
			m_initialized = false;
			Logger::info(LogCategory::RENDER, "Renderer shutdown");
		}
	}

	void Renderer::beginFrame() {
		if (!m_initialized) {
			Logger::error(LogCategory::RENDER, "Renderer not initialized");
			return;
		}

		// Add any per-frame setup here
	}

	void Renderer::endFrame() {
		if (!m_initialized) {
			Logger::error(LogCategory::RENDER, "Renderer not initialized");
			return;
		}

		// Swap buffers
		glfwSwapBuffers(m_window);
	}

	void Renderer::clear(float r, float g, float b, float a) {
		if (!m_initialized) {
			Logger::error(LogCategory::RENDER, "Renderer not initialized");
			return;
		}

		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};