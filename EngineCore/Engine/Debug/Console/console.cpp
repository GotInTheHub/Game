#include "console.h"
#include "../Logger/logger.h"
#include <sstream>

namespace Engine
{

	bool Console::initialize(EngineContext& context)
	{
		m_context = &context;
		return true;
	}

	void Console::shutdown()
	{
		m_context = nullptr;
	}

	void Console::update(float dt)
	{
	}

	void Console::registerCommand(const ConsoleCommand& command)
	{
		if (m_context == nullptr)
			return;

		auto result = m_commands.emplace(command.name, command);

		if (!result.second)
		{
			m_context->get<Logger>().log(
				LogLevel::WARNING,
				LogCategory::ENGINE,
				("Command already registered: " + command.name).c_str()
			);
		}
	}

	void Console::execute(const std::string& line)
	{
		if (m_context == nullptr)
			return;

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
			m_context->get<Logger>().log(
				LogLevel::WARNING,
				LogCategory::ENGINE,
				("Unknown command: " + tokens.front()).c_str()
			);
			return;
		}

		tokens.erase(tokens.begin());

		it->second.callback(*m_context, tokens);
	}

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

	const std::vector<std::string>& Console::getHistory() const
	{
		return m_history;
	}

	void Console::clear()
	{
		m_history.clear();
		m_historyIndex = -1;
	}
}