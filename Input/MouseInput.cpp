//
// Created by Benjam on 13-05-21.
//

#include <SDL2/SDL.h>
#include "MouseInput.h"

namespace Math4BG
{
    MouseInput Mouse = {};

    void MouseInput::MouseSet(MouseButton button, bool state)
    {
        if(button != MouseButton::NoPressed)
        {
            m_mouseState[button] = state;

            if(button == MouseButton::LMB && state)
                m_clickedPosition = m_position;

            if (button == MWU || button == MWD)
                m_notches++;
        }
    }

    void MouseInput::Update()
    {
        for(int i = 0; i < MOUSE_BUTTONS_COUNT; i ++)
            m_prevMouseState[i] = m_mouseState[i];

        m_mouseState[MWU] = false;
        m_mouseState[MWD] = false;

        m_notches = 0;
    }

    MouseButton MouseInput::ConvertSDLInput(uint8_t b) const
    {
        switch(b)
        {
            case SDL_BUTTON_LEFT: return MouseButton::LMB;
            case SDL_BUTTON_RIGHT: return MouseButton::RMB;
            case SDL_BUTTON_MIDDLE: return MouseButton::MMB;
                //case SDL_BUTTON_: return MouseButton::LMB;
                //case SDL_BUTTON_WHEELDOWN: return MouseButton::LMB;
        }

        return MouseButton::NoPressed;
    }

    void MouseInput::MousePos(glm::vec2 position)
    {
        m_lastPosition = m_position;
        m_position = position;
    }
}