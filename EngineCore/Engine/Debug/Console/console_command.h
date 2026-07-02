#pragma once
#include <functional>
#include <string>


namespace Engine {


	struct ConsoleCommand
	{
		using Callback =
			std::function<void(const std::vector<std::string>&)>;
		
		ConsoleCommand(
			std::string commandName,
			std::string commandDescription,
			std::string commandUsage,
			Callback commandCallback)
			: name(std::move(commandName)),
			description(std::move(commandDescription)),
			usage(std::move(commandUsage)),
			callback(std::move(commandCallback))
		{
		}

		std::string name;
		std::string description;
		std::string usage;

		Callback callback;
	};
}