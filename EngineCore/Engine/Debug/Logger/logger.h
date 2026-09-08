#pragma once

#include "log_buffer.h"
#include <thread>
#include <atomic>
#include <fstream>
#include <mutex>
#include <deque>
#include <string_view>
#include "../../Core/engine_system.h"

namespace Engine
{
    class Logger : public IEngineSystem {
    private:
        LogBuffer m_logBuffer;

        std::thread m_worker;
        std::atomic<bool> m_running{ true };

		LogLevel m_minLevel = LogLevel::WARNING;

        std::ofstream m_logFile;
        bool m_fileEnabled = false;

        // retained history for ImGui log window
        std::deque<LogEntry> m_history;
        std::mutex m_historyMutex;

    private:
        void workerThread();

    public:
        Logger() = default;

		~Logger() override;
        bool initialize(EngineContext& context) override;
        void shutdown() override;
		void update(float dt) override;

        void initFile(const std::string& filename);

        void log(LogLevel level, LogCategory category, std::string_view message);

		void setMinLogLevel(LogLevel level) { m_minLevel = level; }

        const std::deque<LogEntry>& getHistory() const;
    };
}