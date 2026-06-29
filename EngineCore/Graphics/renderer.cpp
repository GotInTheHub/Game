#include "renderer.h"
#include <iostream>

Renderer::Renderer() : m_window(nullptr), m_initialized(false) {
}

Renderer::~Renderer() {
	shutdown();
}

bool Renderer::initialize(GLFWwindow* window) {
	if (m_initialized) {
		std::cerr << "Renderer already initialized" << std::endl;
		return false;
	}

	if (window == nullptr) {
		std::cerr << "Window pointer is null" << std::endl;
		return false;
	}

	m_window = window;

	// Make context current
	glfwMakeContextCurrent(m_window);

	// Initialize graphics context (loads GLAD)
	if (!m_graphicsContext.initialize((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize graphics context" << std::endl;
		return false;
	}

	// Set default GL state
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	m_initialized = true;
	std::cout << "Renderer initialized successfully" << std::endl;

	return true;
}

void Renderer::shutdown() {
	if (m_initialized) {
		m_graphicsContext.shutdown();
		m_window = nullptr;
		m_initialized = false;
		std::cout << "Renderer shutdown" << std::endl;
	}
}

void Renderer::beginFrame() {
	if (!m_initialized) {
		std::cerr << "Renderer not initialized" << std::endl;
		return;
	}

	// Add any per-frame setup here
}

void Renderer::endFrame() {
	if (!m_initialized) {
		std::cerr << "Renderer not initialized" << std::endl;
		return;
	}

	// Swap buffers
	glfwSwapBuffers(m_window);
}

void Renderer::clear(float r, float g, float b, float a) {
	if (!m_initialized) {
		std::cerr << "Renderer not initialized" << std::endl;
		return;
	}

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
