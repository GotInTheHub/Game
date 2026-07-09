#pragma once
#include "logger.h"
#include <string>

namespace Engine {
	class OpenGLError {
	public:
		static void clear();
		static bool check(Logger& logger, const std::string& context);
		static bool checkThrottled(Logger& logger, const std::string& context, float throttleSeconds);
	};
}