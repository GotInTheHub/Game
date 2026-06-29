#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicsContext {
private:
	bool m_initialized;

public:
	GraphicsContext();
	~GraphicsContext();

	// Initialize GLAD with the GL loader function
	bool initialize(GLADloadproc loadFunc);

	// Shutdown graphics context
	void shutdown();

	// Get OpenGL version info
	GLint getMajorVersion() const;
	GLint getMinorVersion() const;

	// Check if initialized
	bool isInitialized() const { return m_initialized; }
};
