#pragma once
#include "../EngineCore/input_manager.hpp"
#include "game_action.hpp"

class PlayerController {
public:
	void update(InputManager<GameAction>& input);
};