#pragma once
#include <string>
#include <atomic>

namespace Engine
{
    enum class LogLevel
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
    };

    enum class LogCategory
    {
        ENGINE,
        RENDER,
        AUDIO,
        PHYSICS,
        GAMEPLAY,
        NETWORK,
        GENERAL,
    };

    struct LogEntry {
        LogLevel level;
        LogCategory category;
        char message[256];
        uint64_t timestamp;
    };
}