#pragma once
#include "graphics_context.h"

struct GLFWwindow;

class Renderer {
private:
	GraphicsContext m_graphicsContext;
	GLFWwindow* m_window;
	bool m_initialized;

public:
	Renderer();
	~Renderer();

	// Initialize the renderer with a GLFW window
	bool initialize(GLFWwindow* window);

	// Shutdown the renderer
	void shutdown();

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
