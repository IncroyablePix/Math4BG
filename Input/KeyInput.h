//
// Created by Benjam on 13-05-21.
//

#ifndef MATH4BG_KEYINPUT_H
#define MATH4BG_KEYINPUT_H

#include <cstdint>
#include <glm/glm.hpp>

#define KEY_BUTTONS_COUNT     (4)

namespace Math4BG
{
    enum KeyButton : int32_t
    {
        NoKeyPressed = -1,
        Z = 0,
        Q = 1,
        S = 2,
        D = 3,
        PgUp = 4,
        PgDn = 5,
    };

    class KeyInput
    {
    public:
        KeyInput() = default;
        ~KeyInput() = default;

        KeyButton ConvertSDLInput(uint8_t b) const;
        void KeySet(KeyButton button, bool state);
        void Update();

        inline bool Pressed(KeyButton button) const { return button != NoKeyPressed && (m_keysState[button] && !m_prevKeysState[button]); }
        inline bool Down(KeyButton button) const { return button != NoKeyPressed && m_keysState[button]; }
        inline bool Released(KeyButton button) const { return button != NoKeyPressed && (!m_keysState[button] && m_prevKeysState[button]); }

    private:

        bool m_keysState[KEY_BUTTONS_COUNT] = { false, false, false, false };
        bool m_prevKeysState[KEY_BUTTONS_COUNT] = { false, false, false, false };
    };

    extern KeyInput Keys;
}


#endif //MATH4BG_KEYINPUT_H
