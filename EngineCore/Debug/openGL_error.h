#pragma once

#include <string>

class OpenGLError {
public:
	static void clear();
	static bool check(const std::string& context = "");
	static bool checkThrottled(const std::string& context = "", float throttleSeconds = 1.0f);
};