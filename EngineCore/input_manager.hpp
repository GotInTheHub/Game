#pragma once

#include "keyboard.hpp"
#include "action_map.hpp"

template<typename Action>
class InputManager {
private:
	Keyboard m_keyboard;
	ActionMap<Action> m_actions;

public:
	Keyboard& keyboard() {
		return m_keyboard;
	}

	ActionMap<Action>& actions() {
		return m_actions;
	}

	void update() {
		m_keyboard.update();
	}

	void onKey(Key key, bool pressed) {
		m_keyboard.setKey(key, pressed);
	}
};