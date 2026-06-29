#include "logger.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

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
    std::lock_guard<std::mutex> lock(m_queueMutex);

    m_logFile.open(filename, std::ios::app);
    m_logToFile = m_logFile.is_open();
}

void Logger::shutdown()
{
    bool expected = true;
	if (!m_running.compare_exchange_strong(expected, false)) {
		return; // Already shutting down
	}

	m_cv.notify_all();

	if (m_worker.joinable()) {
		m_worker.join();
	}

	if (m_logFile.is_open()) {
		m_logFile.close();
	}
}

// ---------------- Logging API ----------------

void Logger::log(LogLevel level, LogCategory category, const std::string& message)
{
	if (level < m_minLogLevel) {
		return;
	}

    {
		std::lock_guard<std::mutex> lock(m_queueMutex);
		m_queue.push({ level, category, message });
    }

	m_cv.notify_one();
}

// ---------------- Worker thread ----------------

void Logger::workerThread()
{
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_queueMutex);

        m_cv.wait(lock, [&] {
            return !m_queue.empty() || !m_running;
        });

        while (!m_queue.empty())
        {
            LogMessage msg = std::move(m_queue.front());
            m_queue.pop();
            lock.unlock();

            // timestamp
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);

            char timeStr[26];
            ctime_s(timeStr, sizeof(timeStr), &t);
            timeStr[strcspn(timeStr, "\n")] = 0;

            std::ostringstream out;
            out << "[" << timeStr << "]"
                << " [" << getLevelToString(msg.level) << "]"
                << " [" << getCategoryToString(msg.category) << "] "
                << msg.message;

            std::string final = out.str();

            std::cout << final << std::endl;

            if (m_logToFile && m_logFile.is_open())
            {
                m_logFile << final << std::endl;
            }

            lock.lock();
        };
    };
};

// ---------------- Helpers ----------------

const char* Logger::getLevelToString(LogLevel level) const
{
    switch (level) {
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERROR: return "ERROR";
    case LogLevel::DEBUG: return "DEBUG";
    default: return "UNKNOWN";
    }
}

const char* Logger::getCategoryToString(LogCategory category) const
{
	switch (category) {
	case LogCategory::ENGINE: return "ENGINE";
	case LogCategory::RENDER: return "RENDER";
	case LogCategory::AUDIO: return "AUDIO";
	case LogCategory::PHYSICS: return "PHYSICS";
	case LogCategory::GAMEPLAY: return "GAMEPLAY";
	case LogCategory::NETWORK: return "NETWORK";
	case LogCategory::GENERAL: return "GENERAL";
	default: return "UNKNOWN";
	}
}

// ---------------- Core logging ----------------

void Logger::setMinLogLevel(LogLevel level)
{
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_minLogLevel = level;
}

// ---------------- Convenience ----------------

void Logger::info(LogCategory cat, const std::string& msg)
{
    instance().log(LogLevel::INFO, cat, msg);
}

void Logger::warn(LogCategory cat, const std::string& msg)
{
    instance().log(LogLevel::WARNING, cat, msg);
}

void Logger::error(LogCategory cat, const std::string& msg)
{
    instance().log(LogLevel::ERROR, cat, msg);
}

void Logger::debug(LogCategory cat, const std::string& msg)
{
    instance().log(LogLevel::DEBUG, cat, msg);
}