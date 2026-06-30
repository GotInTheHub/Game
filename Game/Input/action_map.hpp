#pragma once

#include <unordered_map>
#include <utility>

#include "../EngineCore/Input/keyboard.hpp"

namespace Game
{
    template<typename Action>
    class ActionMap
    {
    public:
        void bind(Action a, Engine::Key k)
        {
            m_map[a] = k;
        }

        void bindAxis(Action a, Engine::Key pos, Engine::Key neg)
        {
            m_axes[a] = { pos, neg };
        }

        bool isPressed(Action a, const Engine::Keyboard& kb)
        {
            return kb.isPressed(m_map[a]);
        }

        float getAxis(Action a, const Engine::Keyboard& kb)
        {
            auto& [pos, neg] = m_axes[a];

            float v = 0.0f;
            if (kb.isDown(pos)) v += 1;
            if (kb.isDown(neg)) v -= 1;
            return v;
        }

    private:
        std::unordered_map<Action, Engine::Key> m_map;
        std::unordered_map<Action, std::pair<Engine::Key, Engine::Key>> m_axes;
    };
}