#pragma once

#include "../Window/window.hpp"

namespace Game
{
    class GameInput;
    class PlayerController;
}

namespace Engine
{
    class Engine
    {
    public:
        Engine(int width, int height, const char* title);

        void run();

    private:
        void update(float dt);
        void render();

    private:
        Window m_window;

        // Game layer
        Game::GameInput* m_gameInput = nullptr;
        Game::PlayerController* m_player = nullptr;
    };
}