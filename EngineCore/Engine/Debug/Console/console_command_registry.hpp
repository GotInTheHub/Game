#pragma once
#include "console.h"

namespace Engine
{
	void initCommands()
	{
		Console::instance().registerCommand(
            ConsoleCommand(
                "clear",
                "Clears the console history",
                "clear",
                [](const auto&)
                {
                    Console::instance().clear();
                }
            )
        );
	}
}