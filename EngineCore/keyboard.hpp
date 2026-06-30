#pragma once
#include <array>
#include "key_codes.hpp"

class Keyboard {
private:
	std::array<bool, (size_t)Key::Count> m_current{};
	std::array<bool, (size_t)Key::Count> m_pressedThisFrame{};

public:

	void setKey(Key key, bool pressed);

	bool isDown(Key key) const;
	bool wasPressed(Key key) const;
	
	void endFrame();
};