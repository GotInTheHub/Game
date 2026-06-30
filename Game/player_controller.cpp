#include "player_controller.h"

void PlayerController::update(InputManager<GameAction>& input)
{
	float x = input.actions().getAxis(
		GameAction::MoveRight,
		input.keyboard());

	float z = input.actions().getAxis(
		GameAction::MoveForward,
		input.keyboard());

	//player.move(x, z);

	if (input.actions().isActionPressed(
		GameAction::Jump,
		input.keyboard()))
	{
		//player.jump();
	}
}
