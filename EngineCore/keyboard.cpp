#include "keyboard.hpp"

void Keyboard::setKey(Key key, bool pressed)
{
	if (pressed && !m_current[(size_t)key]) {
		m_pressedThisFrame[(size_t)key] = true;
	}
	
	m_current[(size_t)key] = pressed;
}

bool Keyboard::isDown(Key key) const
{
	return m_current[(size_t)key];
}

bool Keyboard::wasPressed(Key key) const
{
	return m_pressedThisFrame[(size_t)key];
}

void Keyboard::endFrame()
{
	m_pressedThisFrame.fill(false);
}
