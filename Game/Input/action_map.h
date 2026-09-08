#pragma once

#include <array>
#include <utility>
#include <Engine/Input/keyboard.hpp>

namespace Game
{
	template<typename TAction>
	class ActionMap
	{
	public:
		void bind(TAction action, Engine::Key key)
		{
			m_keys[static_cast<size_t>(action)] = key;
		}

		void bindAxis(TAction action, Engine::Key positive, Engine::Key negative)
		{
			m_axes[static_cast<size_t>(action)] = { positive, negative };
		}

		bool isPressed(TAction action, const Engine::Keyboard& keyboard)
		{
			return keyboard.isPressed(m_keys[static_cast<size_t>(action)]);
		}

		bool isDown(TAction action, const Engine::Keyboard& keyboard)
		{
			return keyboard.isDown(m_keys[static_cast<size_t>(action)]);
		}

		float getAxis(TAction action, const Engine::Keyboard& keyboard)
		{
			const auto& [pos, neg] = m_axes[static_cast<size_t>(action)];

			float value = 0.0f;

			if (keyboard.isDown(pos))
				value += 1.0f;

			if (keyboard.isDown(neg))
				value -= 1.0f;

			return value;
		}

	private:
		std::array<Engine::Key, static_cast<size_t>(Engine::Key::Count)> m_keys;
		std::array<std::pair<Engine::Key, Engine::Key>, static_cast<size_t>(Engine::Key::Count)> m_axes;
	};
}