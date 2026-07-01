#include "player_controller.hpp"
#include <iostream>
#include "../../EngineCore/Debug/logger.h"

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
		Logger::info(LogCategory::GAMEPLAY, "Player jumped!");
    }
    void PlayerController::move(float, float)
    {
		Logger::info(LogCategory::GAMEPLAY, "Player moved!");
    }
}