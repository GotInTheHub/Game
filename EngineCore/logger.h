#pragma once

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
private:
    std::ofstream m_logFile;
    bool m_logToFile = false;
    LogLevel m_minLogLevel = LogLevel::INFO;

    std::mutex m_mutex;

    Logger();   // private constructor
    ~Logger();  // private destructor

    const char* getLevelString(LogLevel level) const;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& instance();

    void enableFileLogging(const std::string& filename);
    void setMinLogLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);

    static void info(const std::string& msg);
    static void warning(const std::string& msg);
    static void error(const std::string& msg);
    static void debug(const std::string& msg);
};