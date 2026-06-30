#include "player_controller.h"
#include "game_input.hpp"

void PlayerController::update(InputSystem<GameAction>& input)
{
    input.processEvents();

    auto& kb = input.keyboard();
    auto& a = input.actions();

    float x = a.getAxis(GameAction::MoveRight, kb);
    float z = a.getAxis(GameAction::MoveForward, kb);

    //player.move(x, z);

    if (a.isPressed(GameAction::Jump, kb))
        //player.jump();

    input.endFrame();
}
