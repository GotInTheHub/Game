#include "player_controller.hpp"
#include <iostream>
#include <Engine/Debug/logger.h>
#include <Engine/Input/keyboard.hpp>

namespace Game
{
    void PlayerController::update(ActionMap<GameAction>& input,
        const Engine::Keyboard& kb)
    {
        float x = input.getAxis(GameAction::MoveRight, kb);
        float z = input.getAxis(GameAction::MoveForward, kb);


        if (x != 0.0f || z != 0.0f) {
            move(x, z);
        }

        if (input.isPressed(GameAction::Jump, kb))
            jump();
    }

    void PlayerController::jump()
    {
		Engine::Logger::info(Engine::LogCategory::GAMEPLAY, "Player jumped!");
    }
    void PlayerController::move(float, float)
    {
		Engine::Logger::info(Engine::LogCategory::GAMEPLAY, "Player moved!");
    }
}