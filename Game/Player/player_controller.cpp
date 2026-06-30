#include "player_controller.hpp"

namespace Game
{
    void PlayerController::update(ActionMap<GameAction>& input,
        const Engine::Keyboard& kb)
    {
        float x = input.getAxis(GameAction::MoveRight, kb);
        float z = input.getAxis(GameAction::MoveForward, kb);

        move(x, z);

        if (input.isPressed(GameAction::Jump, kb))
            jump();
    }

    void PlayerController::jump() {}
    void PlayerController::move(float, float) {}
}