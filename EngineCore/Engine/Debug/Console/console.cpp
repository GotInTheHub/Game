#include "console.h"
#include "../Logger/logger.h"
#include <sstream>

namespace Engine
{
	std::vector<std::string> Console::tokenize(const std::string& line) const
	{
		std::stringstream stream(line);

		std::vector<std::string> tokens;

		std::string token;

		while (stream >> token)
		{
			tokens.push_back(token);
		}

		return tokens;
	}

	Console& Engine::Console::instance()
	{
		static Console instance;
		return instance;
	}

	void Console::registerCommand(const ConsoleCommand& command)
	{
		auto result = m_commands.emplace(command.name, command);

		if (!result.second)
		{
			Logger::warn(
				LogCategory::ENGINE,
				("Command already registered: " + command.name).c_str()
			);
		}
	}

	void Console::execute(const std::string& line)
	{
		if (line.empty())
			return;

		m_history.push_back(line);
		m_historyIndex = static_cast<int>(m_history.size());

		auto tokens = tokenize(line);

		if (tokens.empty())
			return;

		auto it = m_commands.find(tokens.front());

		if (it == m_commands.end())
		{
			Logger::warn(
				LogCategory::ENGINE,
				("Unknown command: " + tokens.front()).c_str()
			);
			return;
		}

		tokens.erase(tokens.begin());

		it->second.callback(tokens);
	}

	void Console::clear()
	{
		m_history.clear();
		m_historyIndex = -1;
	}

	const std::vector<std::string>& Console::getHistory() const
	{
		return m_history;
	}

}