//
// Created by Benjam on 13-05-21.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "KeyInput.h"

namespace Math4BG
{
    KeyInput Keys = {};

    void KeyInput::KeySet(KeyButton button, bool state)
    {
        if(button != KeyButton::NoKeyPressed && m_keysState[button] != state)
        {
            m_keysState[button] = state;
        }
    }

    void KeyInput::Update()
    {
        for(int i = 0; i < KEY_BUTTONS_COUNT; i ++)
        {
            m_prevKeysState[i] = m_keysState[i];
            //std::cout << i << ": " << m_keysState[i] << " - " << m_prevKeysState[i] << std::endl;
        }
        //std::cout << std::endl;

    }

    KeyButton KeyInput::ConvertSDLInput(uint8_t b) const
    {
        switch(b)
        {
            case SDLK_z: return KeyButton::Z;
            case SDLK_q: return KeyButton::Q;
            case SDLK_s: return KeyButton::S;
            case SDLK_d: return KeyButton::D;
        }

        return KeyButton::NoKeyPressed;
    }
}