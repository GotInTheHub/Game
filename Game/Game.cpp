#include <iostream>
#include "../EngineCore/window.h"
#include "../EngineCore/Graphics/renderer.h"
#include "../EngineCore/logger.h"
#include "game_input.hpp"

int main() {
	if (!glfwInit()) {
		Logger::error(LogCategory::ENGINE, "Failed to initialize GLFW");
		return -1;
	}

	int exitCode = 0;
	{
		Window window;
		if (!window.isValid()) {
			Logger::error(LogCategory::RENDER, "Failed to create window");
			exitCode = -1;
		}
		else {
			GLFWwindow* glfwWindow = window.getWindow();
			Renderer renderer;
			if (!renderer.initialize(glfwWindow)) {
				Logger::error(LogCategory::RENDER, "Failed to initialize renderer");
				exitCode = -1;
			}
			else {
				//initGameInput();
				while (!glfwWindowShouldClose(glfwWindow)) {
					renderer.beginFrame(0.1f, 0.1f, 0.1f, 1.0f);
					//GameInput::update();
					// Game rendering code goes here

					renderer.endFrame();
					glfwPollEvents();
				}

				renderer.shutdown();
			}

		}
	}

	glfwTerminate();
	return exitCode;
}