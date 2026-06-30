#include "game.hpp"

namespace Game
{
    void Game::initialize(Engine::Engine& engine)
    {
        m_controls.bind(GameAction::Jump, Engine::Key::Space);
        m_controls.bind(GameAction::Shoot, Engine::Key::Escape);
        
        m_controls.bindAxis(GameAction::MoveForward,
            Engine::Key::W,
            Engine::Key::S);

        m_controls.bindAxis(GameAction::MoveRight,
            Engine::Key::D,
            Engine::Key::A);
    }

    void Game::update(Engine::Engine& engine)
    {
        auto& kb = engine.input().keyboard();

        m_player.update(m_controls, kb);
    }

    void Game::render(Engine::Engine&)
    {}

    void Game::shutdown()
    {}
}