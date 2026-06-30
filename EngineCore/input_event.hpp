#pragma once

#include "key_codes.hpp"

enum class InputEventType {
	KeyPressed,
	KeyReleased,
	MouseButtonPress,
	MouseButtonRelease,
	MouseMove,
	MouseScroll
};

struct InputEvent {
	Key key;
	InputEventType type;
};