#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "console_command.h"

namespace Engine {
	class Console
	{
	private:
		std::unordered_map<std::string, ConsoleCommand> m_commands;
		std::vector<std::string> m_history;
		int m_historyIndex = -1;

	private:
		Console() = default;
		~Console() = default;

		Console(const Console&) = delete;
		Console& operator=(const Console&) = delete;

		std::vector<std::string> tokenize(const std::string& line) const;

	public:
		static Console& instance();

		void registerCommand(const ConsoleCommand& command);

		void execute(const std::string& line);

		void clear();

		const std::vector<std::string>& getHistory() const;
	};
}