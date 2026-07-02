#pragma once

#include "../Window/window.hpp"
#include "../Input/input_system.hpp"

namespace Engine
{
    class Engine
    {
    public:
        Engine(int width, int height, const char* title);

        void beginFrame();
        void endFrame();

        bool isRunning() const;
        void quit();

        Window& window();
		InputSystem& input();

    private:
        Window m_window;
		InputSystem m_input;
    };
}