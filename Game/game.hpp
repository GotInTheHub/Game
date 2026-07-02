#pragma once

#include <Engine/Core/engine.hpp>
#include "Input/game_action.hpp"
#include "Player/player_controller.hpp"
#include "Input/action_map.hpp"

namespace Game
{
    class Game
    {
    public:
        void initialize(Engine::Engine& engine);
        void update(Engine::Engine& engine);
        void render(Engine::Engine& engine);
        void shutdown();

    private:
        PlayerController m_player;
        ActionMap<GameAction> m_controls;
    };
}