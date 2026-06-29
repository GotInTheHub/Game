#pragma once
#include <string>
#include <atomic>

enum class LogLevel { INFO, WARNING, ERROR, DEBUG };
enum class LogCategory { ENGINE, RENDER, AUDIO, PHYSICS, GAMEPLAY, NETWORK, GENERAL };

struct LogEntry {
    LogLevel level;
    LogCategory category;
    char message[256];
    uint64_t timestamp;
};