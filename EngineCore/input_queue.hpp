#pragma once

#include "input_event.hpp"
#include <queue>

class InputQueue {
private:
	std::queue<InputEvent> m_queue;

public:
	void push(const InputEvent& event) {
		m_queue.push(event);
	}

	bool empty() const {
		return m_queue.empty();
	}

	InputEvent pop() {
		InputEvent event = m_queue.front();
		m_queue.pop();
		return event;
	}
};