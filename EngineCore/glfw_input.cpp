#include "glfw_input.h"
#include "input_event.hpp"
#include "logger.h"

static InputQueue* g_queue = nullptr;

static Key convertKey(int glfwKey) {
	switch (glfwKey)
	{
		case GLFW_KEY_W: return Key::W;
		case GLFW_KEY_A: return Key::A;
		case GLFW_KEY_S: return Key::S;
		case GLFW_KEY_D: return Key::D;
		case GLFW_KEY_SPACE: return Key::Space;
		case GLFW_KEY_ESCAPE: return Key::Escape;
		case GLFW_MOUSE_BUTTON_LEFT: return Key::MouseLeft;
		case GLFW_MOUSE_BUTTON_RIGHT: return Key::MouseRight;
		default: return Key::Count; // Invalid key
	}
}

static void keyCallback(GLFWwindow*, int key, int, int action, int)
{
	if (!g_queue) return;

	InputEvent e;
	e.key = convertKey(key);
	e.type = (action == GLFW_PRESS)
		? InputEventType::KeyPressed
		: InputEventType::KeyReleased;

	Logger::debug(LogCategory::ENGINE, e.type == InputEventType::KeyPressed ? "Key Pressed" : "Key Released");
	Logger::debug(LogCategory::ENGINE, "Key code: " + key);
}

void initGLFWInput(GLFWwindow* window, InputQueue& queue)
{
	g_queue = &queue;

	glfwSetKeyCallback(window, keyCallback);
}