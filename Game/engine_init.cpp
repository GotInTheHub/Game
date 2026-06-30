#include "game_input.hpp"
#include "../EngineCore/glfw_input.h"
#include <GLFW/glfw3.h>

void initEngine(GLFWwindow* window, GameInput& input)
{
	initGLFWInput(window, input.queue());
}