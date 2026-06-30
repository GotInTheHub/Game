#include "game_input.hpp"
#include "game_action.hpp"

void initGameInput(GameInput& input) {

	input.actions().bindAction(GameAction::Jump, Key::Space);
	input.actions().bindAction(GameAction::Shoot, Key::MouseLeft);
	input.actions().bindAction(GameAction::Pause, Key::Escape);
	
	input.actions().bindAxis(GameAction::MoveForward, Key::W, Key::S);
	input.actions().bindAxis(GameAction::MoveRight, Key::D, Key::A);
}