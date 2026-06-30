#pragma once

#include "key.hpp"
#include <array>

namespace Engine
{
    enum class KeyState
    {
        Up,        // not pressed
        Pressed,   // just pressed this frame
        Down,      // held down
        Released   // just released this frame
    };

    class Keyboard
    {
    public:
        Keyboard();

        // Called by engine (Window layer)
        void press(Key key);
        void release(Key key);

        // Called once per frame
        void update();

        // Query API (used by game)
        bool isDown(Key key) const;
        bool isPressed(Key key) const;
        bool isReleased(Key key) const;

        KeyState getState(Key key) const;

    private:
        std::array<KeyState, static_cast<size_t>(Key::Count)> m_states;
    };
}