#include "graphics_context.h"
#include <iostream>

namespace Engine {
	GraphicsContext::GraphicsContext() : m_initialized(false) {}

	GraphicsContext::~GraphicsContext() {
		shutdown();
	}

	bool GraphicsContext::initialize(GLADloadproc loadFunc) {
		if (m_initialized) {
			std::cerr << "GraphicsContext already initialized" << std::endl;
			return false;
		}

		// Load OpenGL functions using GLAD
		if (!gladLoadGLLoader(loadFunc)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		m_initialized = true;

		// Log OpenGL version
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		return true;
	}

	void GraphicsContext::shutdown() {
		// Currently no cleanup needed for GLAD
		m_initialized = false;
	}

	GLint GraphicsContext::getMajorVersion() const {
		GLint major = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		return major;
	}

	GLint GraphicsContext::getMinorVersion() const {
		GLint minor = 0;
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		return minor;
	}
}