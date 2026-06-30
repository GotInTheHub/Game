#pragma once

#include "../EngineCore/input_system.hpp"
#include "game_action.hpp"

using GameInput = InputSystem<GameAction>;

void initGameInput(GameInput& input);