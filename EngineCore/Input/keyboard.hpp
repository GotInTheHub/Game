#pragma once
#include <array>
#include "key.hpp"

namespace Engine
{
    class Keyboard
    {
    public:
        void press(Key key);
        void release(Key key);

        void update();

        bool isDown(Key key) const;
        bool isPressed(Key key) const;

    private:
        std::array<bool, (size_t)Key::Count> m_current{};
        std::array<bool, (size_t)Key::Count> m_pressed{};
    };
}