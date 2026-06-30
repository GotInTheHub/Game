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

        void beginFrame();

        bool isDown(Key key) const;
        bool isPressed(Key key) const;

    private:
        std::array<bool, static_cast<size_t>(Key::Count)> m_down{};
        std::array<bool, static_cast<size_t>(Key::Count)> m_pressed{};
    };
}