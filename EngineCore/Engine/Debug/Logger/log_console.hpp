#pragma once
#include <imgui.h>
#include "logger.h"

namespace Engine {
    class LogConsole {
    private:
        bool m_showInfo = true;
        bool m_showWarning = true;
        bool m_showError = true;
        bool m_showDebug = true;

        char m_filter[128] = "";

    public:
        void draw()
        {
            ImGui::Begin("Console");

            ImGui::InputText("Filter", m_filter, sizeof(m_filter));

            ImGui::Checkbox("Info", &m_showInfo);
            ImGui::SameLine();
            ImGui::Checkbox("Warn", &m_showWarning);
            ImGui::SameLine();
            ImGui::Checkbox("Error", &m_showError);
            ImGui::SameLine();
            ImGui::Checkbox("Debug", &m_showDebug);

            ImGui::Separator();

            const auto& logs = Logger::instance().getHistory();

            for (const auto& l : logs)
            {
                if (!passesFilter(l))
                    continue;

                ImVec4 color;
                switch (l.level)
                {
                case LogLevel::INFO: color = { 1,1,1,1 }; break;
                case LogLevel::WARNING: color = { 1,1,0,1 }; break;
                case LogLevel::ERROR: color = { 1,0.3f,0.3f,1 }; break;
                case LogLevel::DEBUG: color = { 0.6f,0.6f,1,1 }; break;
                }

                ImGui::TextColored(color, "%s", l.message);
            }

            ImGui::End();
        }

        bool passesFilter(const LogEntry& e)
        {
            if (e.level == LogLevel::INFO && !m_showInfo) return false;
            if (e.level == LogLevel::WARNING && !m_showWarning) return false;
            if (e.level == LogLevel::ERROR && !m_showError) return false;
            if (e.level == LogLevel::DEBUG && !m_showDebug) return false;

            if (strlen(m_filter) > 0 && strstr(e.message, m_filter) == nullptr)
                return false;

            return true;
        }
    };
}