#pragma once

#include <Engine/Core/engine.h>
#include "game.hpp"

namespace Game
{
    class Application
    {
    public:
        Application();

        void run();

    private:
        Engine::Engine m_engine;
        Game m_game;
    };
}