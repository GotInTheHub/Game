#include "logger.h"

#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include <cstring>

// ---------------- Singleton ----------------

Logger& Logger::instance()
{
    static Logger inst;
    return inst;
}

// ---------------- Constructor / Destructor ----------------

Logger::Logger() = default;

Logger::~Logger()
{
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

// ---------------- Helpers ----------------

const char* Logger::getLevelString(LogLevel level) const
{
    switch (level) {
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERROR: return "ERROR";
    case LogLevel::DEBUG: return "DEBUG";
    default: return "UNKNOWN";
    }
}

// ---------------- Core logging ----------------

void Logger::enableFileLogging(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_logFile.open(filename, std::ios::app);
    m_logToFile = m_logFile.is_open();
}

void Logger::setMinLogLevel(LogLevel level)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_minLogLevel = level;
}

void Logger::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (level < m_minLogLevel)
        return;

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    char timeStr[26];
    ctime_s(timeStr, sizeof(timeStr), &time);

    // remove newline
    timeStr[strcspn(timeStr, "\n")] = 0;

    std::stringstream ss;
    ss << "[" << timeStr << "] ["
        << getLevelString(level) << "] "
        << message;

    std::cout << ss.str() << std::endl;

    if (m_logToFile && m_logFile.is_open()) {
        m_logFile << ss.str() << std::endl;
        m_logFile.flush();
    }
}

// ---------------- Convenience wrappers ----------------

void Logger::info(const std::string& msg)
{
    instance().log(LogLevel::INFO, msg);
}

void Logger::warning(const std::string& msg)
{
    instance().log(LogLevel::WARNING, msg);
}

void Logger::error(const std::string& msg)
{
    instance().log(LogLevel::ERROR, msg);
}

void Logger::debug(const std::string& msg)
{
    instance().log(LogLevel::DEBUG, msg);
}