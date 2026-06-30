#pragma once
#include "../Input/key.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
    inline Key translateKey(int key)
    {
        switch (key)
        {
            case GLFW_KEY_A: return Key::A;
            case GLFW_KEY_B: return Key::B;
            case GLFW_KEY_C: return Key::C;
            case GLFW_KEY_D: return Key::D;
            case GLFW_KEY_W: return Key::W;
            case GLFW_KEY_S: return Key::S;
            case GLFW_KEY_SPACE: return Key::Space;
            case GLFW_KEY_ESCAPE: return Key::Escape;
            default: return Key::Unknown;
        }
    }
}