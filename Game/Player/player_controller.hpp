#pragma once

#include "../Input/game_input.hpp"

namespace Game
{
	class PlayerController
	{
	public:
		void update(GameInput& input, float dt);
	};
}