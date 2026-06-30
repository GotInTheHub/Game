#include "player_controller.hpp"
#include "../EngineCore/Input/keyboard.hpp"

namespace Game
{
	void PlayerController::update(GameInput& input, float dt)
	{
		auto& kb = input.actions();

		float x = kb.getAxis(Action::MoveRight, kb);
		float z = kb.getAxis(Action::MoveForward, kb);

		if (kb.isPressed(Action::Jump, kb))
		{
			// Handle jump action
		}

		if (kb.isPressed(Action::Shoot, kb))
		{
			// Handle shoot action
		}
	}
}