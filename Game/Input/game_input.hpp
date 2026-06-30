#pragma once

#include "game_action.hpp"
#include "action_map.hpp"

namespace Game
{
	class GameInput
	{
	private:
		ActionMap<GameAction> m_actions;

	public:
		ActionMap<GameAction>& actions()
		{
			return m_actions;
		}
	};
}