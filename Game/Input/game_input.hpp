#pragma once

#include "game_action.hpp"
#include "action_map.hpp"

namespace Game
{
	class GameInput
	{
	private:
		ActionMap<Action> m_actions;

	public:
		ActionMap<Action>& actions()
		{
			return m_actions;
		}
	};
}