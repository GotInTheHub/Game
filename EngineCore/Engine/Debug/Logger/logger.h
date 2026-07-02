#pragma once

#include "log_buffer.h"
#include <thread>
#include <atomic>
#include <fstream>
#include <mutex>
#include <vector>

namespace Engine
{
    class Logger {
    private:
        LogBuffer m_logBuffer;

        std::thread m_worker;
        std::atomic<bool> m_running{ true };


        std::ofstream m_logFile;
        bool m_fileEnabled = false;

        // retained history for ImGui log window
        std::vector<LogEntry> m_history;
        std::mutex m_historyMutex;

    private:
        Logger();
        ~Logger();

        void workerThread();

    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& instance();

        void initFile(const std::string& filename);
        void shutdown();

        void log(LogLevel level, LogCategory category, const char* message);

        const std::vector<LogEntry>& getHistory() const;

        static void info(LogCategory c, const char* m);
        static void warn(LogCategory c, const char* m);
        static void error(LogCategory c, const char* m);
        static void debug(LogCategory c, const char* m);
    };
}