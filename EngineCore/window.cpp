#include "window.h"
#include "logger.h"
#include "glfw_input.cpp"

int Window::setupWindow(std::string& windowName)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, windowName.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		Logger::error(LogCategory::ENGINE, "Failed to create GLFW window");
		return -1;
	}

	glfwMakeContextCurrent(m_window);

	setupCallbacks();

	return 0;
}

void Window::setupCallbacks()
{
	//glfwSetKeyCallback() inside glfw_input.cpp handles key input callbacks
}

Window::Window()
	: m_window(nullptr),
	m_width(Config::getInstance().m_screenWidth),
	m_height(Config::getInstance().m_screenHeight),
	m_name("default")
{
	setupWindow(m_name);
}

Window::Window(int width, int height, const char* name)
	: m_window(nullptr),
	m_width(width),
	m_height(height),
	m_name(name)
{
	setupWindow(this->m_name);
}

Window::~Window()
{
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
}
