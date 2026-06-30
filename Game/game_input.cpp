#include "game_input.hpp"

void initGameInput(GameInput& input)
{
    auto& a = input.actions();

    a.bindAction(GameAction::Jump, Key::Space);
    a.bindAction(GameAction::Shoot, Key::MouseLeft);
    a.bindAction(GameAction::Pause, Key::Escape);

    a.bindAxis(GameAction::MoveForward, Key::W, Key::S);
    a.bindAxis(GameAction::MoveRight, Key::D, Key::A);
}