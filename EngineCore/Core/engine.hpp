#pragma once

#include "../Window/window.hpp"

namespace Engine
{
    class Engine
    {
    public:
        Engine(int width, int height, const char* title);

        void beginFrame();
        void endFrame();

        bool isRunning() const;

        Window& window();

    private:
        Window m_window;
    };
}