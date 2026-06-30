#include "engine.hpp"
#include <GLFW/glfw3.h>

#include "../../Game/Input/game_input.hpp"
#include "../../Game/Player/player_controller.hpp"

namespace Engine
{
	Engine::Engine(int width, int height, const char* title)
		: m_window(width, height, title)
	{
	}

	void Engine::run()
	{
		Game::GameInput gameInput;
		Game::PlayerController player;

		double lastTime = glfwGetTime();

		while (!m_window.shouldClose())
		{
			double currentTime = glfwGetTime();
			float dt = static_cast<float>(currentTime - lastTime);
			lastTime = currentTime;

			m_window.pollEvents();

			update(dt);

			player.update(gameInput, dt);

			render();

			m_window.input().endFrame();
			m_window.swapBuffers();
		}
	}

	void Engine::update(float dt)
	{
		// Update game logic here
	}

	void Engine::render()
	{
		// Render game here
	}
}