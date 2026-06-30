#pragma once
#include "../EngineCore/input_system.hpp"
#include "game_action.hpp"

class PlayerController {
public:
	void update(InputSystem<GameAction>& input);
};