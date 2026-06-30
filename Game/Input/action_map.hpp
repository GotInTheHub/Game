#pragma once

#include <unordered_map>
#include <utility>

#include "../EngineCore/Input/keyboard.hpp"

namespace Game
{
    template<typename TAction>
    class ActionMap
    {
    public:
        void bind(TAction action, Engine::Key key)
        {
            m_keys[action] = key;
        }

        void bindAxis(TAction action,
            Engine::Key positive,
            Engine::Key negative)
        {
            m_axes[action] = { positive, negative };
        }

        bool isPressed(TAction action,
            const Engine::Keyboard& keyboard)
        {
            auto it = m_keys.find(action);
            if (it == m_keys.end()) return false;

            return keyboard.isPressed(it->second);
        }

        bool isDown(TAction action,
            const Engine::Keyboard& keyboard)
        {
            auto it = m_keys.find(action);
            if (it == m_keys.end()) return false;

            return keyboard.isDown(it->second);
        }

        float getAxis(TAction action,
            const Engine::Keyboard& keyboard)
        {
            auto it = m_axes.find(action);
            if (it == m_axes.end()) return 0.0f;

            const auto& [pos, neg] = it->second;

            float value = 0.0f;

            if (keyboard.isDown(pos))
                value += 1.0f;

            if (keyboard.isDown(neg))
                value -= 1.0f;

            return value;
        }

    private:
        std::unordered_map<TAction, Engine::Key> m_keys;
        std::unordered_map<TAction, std::pair<Engine::Key, Engine::Key>> m_axes;
    };
}