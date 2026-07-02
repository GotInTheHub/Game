#pragma once

#include "engine.hpp"
#include "../../Game/game.hpp"

namespace Engine
{
    class Application
    {
    public:
        Application();

        void run();

    private:
        Engine m_engine;
        Game::Game m_game;
    };
}