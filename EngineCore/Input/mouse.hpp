#pragma once

#include <array>
#include <glm/glm.hpp>

namespace Engine
{
    enum class MouseButton { Left, Right, Middle, Count };

    class Mouse
    {
    public:
        void press(MouseButton b);
        void release(MouseButton b);

        void setPosition(float x, float y);
        void update();

        bool isDown(MouseButton b) const;
        bool isPressed(MouseButton b) const;

        glm::vec2 position() const;
        glm::vec2 delta() const;

    private:
        std::array<bool, 3> m_current{};
        std::array<bool, 3> m_pressed{};

        glm::vec2 m_pos{};
        glm::vec2 m_last{};
        glm::vec2 m_delta{};
    };
}