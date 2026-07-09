#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "console_command.h"
#include "../Logger/logger.h"
#include "../../Core/engine_system.h"
#include "../../Core/engine_context.h"

namespace Engine {
	class Console : public IEngineSystem
	{
	private:
		std::unordered_map<std::string, ConsoleCommand> m_commands;
		std::vector<std::string> m_history;
		int m_historyIndex = -1;

		EngineContext* m_context = nullptr;

	private:
		std::vector<std::string> tokenize(const std::string& line) const;

	public:

		Console() = default;
		bool initialize(EngineContext& context) override;
		void shutdown() override;
		void update(float dt) override;

		void registerCommand(const ConsoleCommand& command);
		void execute(const std::string& line);
		void clear();


		const std::vector<std::string>& getHistory() const;
	};
}