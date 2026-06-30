#pragma once

#include "../../EngineCore/Input/keyboard.hpp"
#include "../../EngineCore/Input/mouse.hpp"

#include <unordered_map>
#include <utility>

namespace Game
{
	template<typename Action>
	class ActionMap
	{
	private:
		std::unordered_map<Action, Engine::Key> m_actions;
		std::unordered_map<Action, std::pair<Engine::Key, Engine::Key>> m_axes;

	public:
		void bind(Action action, Engine::Key key)
		{
			m_actions[action] = key;
		}

		void bindAxis(Action action, Engine::Key positive, Engine::Key negative)
		{
			m_axes[action] = std::make_pair(positive, negative);
		}

		bool isPressed(Action action, const Engine::Keyboard& kb) const
		{
			auto it = m_actions.find(action);
			if (it == m_actions.end())
				return false;

			return kb.isPressed(it->second);
		}

		bool isDown(Action action, const Engine::Keyboard& kb) const
		{
			auto it = m_actions.find(action);
			if (it == m_actions.end())
				return false;
		
			return kb.isDown(it->second);
		}

		float getAxis(Action action, const Engine::Keyboard& kb) const
		{
			auto it = m_axes.find(action);
			if(it == m_axes.end())
				return 0.0f;

			float value = 0.0f;

			if (kb.isDown(it->second.first))
				value += 1.0f;

			if (kb.isDown(it->second.second))
				value -= 1.0f;

			return value;
		}
	};
}