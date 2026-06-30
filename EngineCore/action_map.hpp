#pragma once
#include "keyboard.hpp"
#include <unordered_map>
#include <utility>

template<typename Action>
class ActionMap {
public:

	void bindAction(Action action, Key key) {
		m_actions[action] = key;
	}

	void bindAxis(Action axis, Key positiveKey, Key negativeKey) {
		m_axes[axis] = std::make_pair(positiveKey, negativeKey);
	}

	bool isActionPressed(Action action, const Keyboard& keyboard) const {
		auto it = m_actions.find(action);
		if (it == m_actions.end())
			return false;

		return keyboard.wasPressed(it->second);
	}

	bool isActionReleased(Action action, const Keyboard& keyboard) const {
		auto it = m_actions.find(action);
		if (it == m_actions.end())
			return false;

		return keyboard.isDown(it->second);
	}

	float getAxis(Action axis, const Keyboard& keyboard) const {
		auto it = m_axes.find(axis);
		if (it == m_axes.end())
			return 0.0f;

		float value = 0.0f;

		if (keyboard.isDown(it->second.first))
			value += 1.0f;

		if (keyboard.isDown(it->second.second))
			value -= 1.0f;

		return value;
	}

private:
	std::unordered_map<Action, Key> m_actions;
	std::unordered_map<Action, std::pair<Key, Key>> m_axes;
};