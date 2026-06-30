#pragma once

#include "../EngineCore/input_manager.hpp"
#include "game_action.hpp"

using GameInput = InputManager<GameAction>;

void initGameInput(GameInput& input);
