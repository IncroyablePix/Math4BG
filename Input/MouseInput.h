//
// Created by Benjam on 13-05-21.
//

#ifndef MATH4BG_MOUSEINPUT_H
#define MATH4BG_MOUSEINPUT_H

#include <glm/glm.hpp>

#define MOUSE_BUTTONS_COUNT     (5)

namespace Math4BG
{
    enum MouseButton : int32_t
    {
        NoPressed = -1,
        LMB = 0,
        RMB = 1,
        MMB = 2,
        MWU = 3,
        MWD = 4
    };

    class MouseInput
    {
    public:
        MouseInput() = default;
        ~MouseInput() = default;

        MouseButton ConvertSDLInput(uint8_t b) const;
        void MouseSet(MouseButton button, bool state);
        void MousePos(glm::vec2 position);
        void Update();

        inline const glm::vec2 Position() const { return m_position; }
        inline const glm::vec2 DeltaPosition() const { return m_position - m_lastPosition; }
        inline const glm::vec2 FromClickedPos() const { return m_position - m_clickedPosition; }
        inline bool Pressed(MouseButton button) const { return button != NoPressed && (m_mouseState[button] && !m_prevMouseState[button]); }
        inline bool Down(MouseButton button) const { return button != NoPressed && m_mouseState[button]; }
        inline bool Released(MouseButton button) const { return button != NoPressed && (!m_mouseState[button] && m_prevMouseState[button]); }

    private:

        int m_notches = 0;
        bool m_mouseState[MOUSE_BUTTONS_COUNT] = { false, false, false, false, false };
        bool m_prevMouseState[MOUSE_BUTTONS_COUNT] = { false, false, false, false, false };
        glm::vec2 m_position;
        glm::vec2 m_lastPosition;
        glm::vec2 m_clickedPosition;
    };

    extern MouseInput Mouse;
}

#endif //MATH4BG_MOUSEINPUT_H
