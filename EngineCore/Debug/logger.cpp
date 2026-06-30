#include "logger.h"
#include <chrono>
#include <cstring>
#include <iostream>

// ---------------- Singleton ----------------

Logger& Logger::instance()
{
    static Logger inst;
    return inst;
}

// ---------------- Lifecycle ----------------

Logger::Logger()
{
    m_worker = std::thread(&Logger::workerThread, this);
}

Logger::~Logger()
{
    shutdown();
}

// ---------------- Init / Shutdown ----------------

void Logger::initFile(const std::string& filename)
{
    m_logFile.open(filename, std::ios::app);
    m_fileEnabled = m_logFile.is_open();
}

void Logger::shutdown()
{
	m_running = false;

	if (m_worker.joinable()) {
		m_worker.join();
	}

	if (m_logFile.is_open()) {
		m_logFile.close();
	}
}

// ---------------- Logging API ----------------

void Logger::log(LogLevel level, LogCategory category, const char* message)
{
    LogEntry e{};
	e.level = level;
	e.category = category;
    e.timestamp = 
        (uint64_t)std::chrono::high_resolution_clock::now()
		.time_since_epoch().count();

    strncpy_s(e.message, message, sizeof(e.message) - 1);

    m_logBuffer.push(e);
}

const std::vector<LogEntry>& Logger::getHistory() const
{
    return m_history;
}

// ---------------- Worker thread ----------------

void Logger::workerThread()
{
    while (m_running) {
        LogEntry e;

        while (m_running)
        {
            while (m_logBuffer.pop(e))
            {
                {
                    std::lock_guard<std::mutex> lock(m_historyMutex);
                    m_history.push_back(e);
                    if (m_history.size() > 10000)
                        m_history.erase(m_history.begin());
                }

                std::cout << e.message << std::endl;

                if (m_fileEnabled)
                    m_logFile << e.message << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
};

// ---------------- Convenience ----------------

void Logger::info(LogCategory cat, const char* msg)
{
    instance().log(LogLevel::INFO, cat, msg);
}

void Logger::warn(LogCategory cat, const char* msg)
{
    instance().log(LogLevel::WARNING, cat, msg);
}

void Logger::error(LogCategory cat, const char* msg)
{
    instance().log(LogLevel::ERROR, cat, msg);
}

void Logger::debug(LogCategory cat, const char* msg)
{
    instance().log(LogLevel::DEBUG, cat, msg);
}