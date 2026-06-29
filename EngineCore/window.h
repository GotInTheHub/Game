#pragma once
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.hpp"
#include <string>

class Window {
private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	std::string m_name;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	int setupWindow(std::string& name);

public:
	Window();
	Window(int width, int height, const char* name);
	~Window();

	GLFWwindow* getWindow() const { return m_window; }
	bool isValid() const { return m_window != nullptr; }
};