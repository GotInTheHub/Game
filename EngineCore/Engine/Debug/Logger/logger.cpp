#include "logger.h"
#include <chrono>
#include <cstring>
#include <iostream>

namespace Engine {
    // ---------------- Lifecycle ----------------

    Logger::~Logger()
    {
        shutdown();
    }

    bool Logger::initialize(EngineContext& context)
    {
        m_running = true;

		m_worker = std::thread(&Logger::workerThread, this);

        return m_running;
    }

    void Logger::update(float dt)
    {
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

    void Logger::log(LogLevel level, LogCategory category, std::string_view message)
    {
        if (level < m_minLevel) return;

        LogEntry e{};
        e.level = level;
        e.category = category;
        e.timestamp =
            (uint64_t)std::chrono::high_resolution_clock::now()
            .time_since_epoch().count();
        
        const size_t maxLen = sizeof(e.message) - 1;
        const size_t len = message.size() < maxLen ? message.size() : maxLen;
        std::memcpy(e.message, message.data(), len);
        e.message[len] = '\0';

        m_logBuffer.push(e);
    }

    const std::deque<LogEntry>& Logger::getHistory() const
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

                    std::cout << e.message << '\n';

                    if (m_fileEnabled)
                        m_logFile << e.message << '\n';
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    };
}