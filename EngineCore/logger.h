#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

enum class LogCategory {
    ENGINE,
    RENDER,
    AUDIO,
    PHYSICS,
    GAMEPLAY,
    NETWORK,
    GENERAL
};

struct LogMessage {
    LogLevel level;
    LogCategory category;
    std::string message;
};

class Logger {
private:
    std::ofstream m_logFile;

    std::mutex m_queueMutex;
	std::condition_variable m_cv;
	std::queue<LogMessage> m_queue;

    std::thread m_worker;
	std::atomic<bool> m_running{ true };

    LogLevel m_minLogLevel = LogLevel::DEBUG;
    bool m_logToFile = false;

    Logger();
    ~Logger();

    void workerThread();

    const char* getLevelToString(LogLevel level) const;
	const char* getCategoryToString(LogCategory category) const;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& instance();

    void initFile(const std::string& filename);
	void shutdown();

    void log(LogLevel level, LogCategory category, const std::string& message);

    void setMinLogLevel(LogLevel level);

    static void info(LogCategory cat, const std::string& msg);
    static void warn(LogCategory cat, const std::string& msg);
    static void error(LogCategory cat, const std::string& msg);
    static void debug(LogCategory cat, const std::string& msg);
};