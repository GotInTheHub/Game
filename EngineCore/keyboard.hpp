#pragma once
#include <array>
#include "key_codes.hpp"

class Keyboard {
private:
	std::array<bool, static_cast<size_t>(Key::Count)> m_current{};
	std::array<bool, static_cast<size_t>(Key::Count)> m_previous{};

public:

	void setKey(Key key, bool pressed);
	bool isDown(Key key) const;
	bool wasPressed(Key key) const;
	bool wasReleased(Key key) const;
	void update();
};