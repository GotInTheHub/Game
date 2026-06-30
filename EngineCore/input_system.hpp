#pragma once

#include "input_queue.hpp"
#include "keyboard.hpp"

template<typename Action>
class ActionMap;

template<typename Action>
class InputSystem {
private:
	InputQueue m_queue;
	Keyboard m_keyboard;
	ActionMap<Action> m_actions;

public:
	InputQueue& queue() { return m_queue; }
	Keyboard& keyboard() { return m_keyboard; }
	ActionMap<Action>& actions() { return m_actions; }

	void processEvents()
	{
		while (!m_queue.empty()) {
			auto e = m_queue.pop();
			m_keyboard.setKey(
				e.key,
				e.type == InputEventType::KeyPressed
			);
		}
	}

	void endFrame()
	{
		m_keyboard.endFrame();
	}
};