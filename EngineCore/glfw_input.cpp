#include "input_manager.hpp"
#include "key_codes.hpp"
#include <GLFW/glfw3.h>

template<typename Action>
static InputManager<Action>* g_input = nullptr;

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

template<typename Action>
void keyCallback(GLFWwindow*, int key, int, int action, int)
{
	if (!g_input<Action>) return;

	g_input<Action>->onKey(
		convertKey(key),
		action != GLFW_RELEASE);
}

template<typename Action>
void initGLFWInput(GLFWwindow* window, InputManager<Action>& input)
{
	g_input<Action> = &input;

	glfwSetKeyCallback(window, keyCallback<Action>);
}