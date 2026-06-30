#pragma once

#include "../Input/action_map.hpp"
#include "../Input/game_action.hpp"

namespace Game
{
    class PlayerController
    {
    public:
        void update(ActionMap<GameAction>& input,
            const Engine::Keyboard& kb);

        void jump();
        void move(float x, float z);
    };
}