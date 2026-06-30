#pragma once
#include "keyboard.hpp"
#include <unordered_map>

template<typename Action>
class ActionMap {
public:

	void bindAction(Action action, Key key) {
		m_actions[action] = key;
	}

	void bindAxis(Action axis, Key positiveKey, Key negativeKey) {
		m_axes[axis] = std::make_pair(positiveKey, negativeKey);
	}

	bool isPressed(Action action, const Keyboard& keyboard) const {
		return keyboard.wasPressed(m_actions.at(action));
	}

	bool isDown(Action action, const Keyboard& keyboard) const {
		return keyboard.isDown(m_actions.at(action));
	}

	float getAxis(Action axis, const Keyboard& keyboard) const {
		
		auto [pos, neg] = m_axes.at(axis);

		float value = 0.0f;

		if (keyboard.isDown(pos))
			value += 1.0f;

		if (keyboard.isDown(neg))
			value -= 1.0f;

		return value;
	}

private:
	std::unordered_map<Action, Key> m_actions;
	std::unordered_map<Action, std::pair<Key, Key>> m_axes;
};