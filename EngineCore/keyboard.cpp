#include "keyboard.hpp"

void Keyboard::setKey(Key key, bool pressed)
{
	m_current[(size_t)key] = pressed;
}

bool Keyboard::isDown(Key key) const
{
	return m_current[(size_t)key];
}

bool Keyboard::wasPressed(Key key) const
{
	return m_current[(size_t)key] && !m_previous[(size_t)key];
}

bool Keyboard::wasReleased(Key key) const
{
	return !m_current[(size_t)key] && m_previous[(size_t)key];
}

void Keyboard::update()
{
	m_previous = m_current;
}
