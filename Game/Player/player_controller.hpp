#pragma once

#include "../Input/action_map.h"
#include "../Input/game_action.hpp"
#include <Engine/Input/keyboard.hpp>
#include <Engine/Core/engine_context.h>

namespace Game
{
    class PlayerController
    {
    public:
		void initialize(Engine::EngineContext& context);
        void update(ActionMap<GameAction>& input,
            const Engine::Keyboard& kb);

        void jump();
        void move(float x, float z);

    private:
		float m_speed = 5.0f;
		Engine::EngineContext* m_context = nullptr;
    };
}