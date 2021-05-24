//
// Created by Benjam on 24-05-21.
//

#ifndef MATH4BG_SOUND_H
#define MATH4BG_SOUND_H

#include <memory>
#include <SDL2/SDL.h>

namespace Math4BG
{
    class Sound : public std::enable_shared_from_this<Sound>
    {
    public:
        virtual ~Sound() = default;
        virtual void Play() = 0;
        virtual void Stop() = 0;
        virtual void Pause() = 0;

    protected:
        uint32_t m_length;
    };
}

#endif //MATH4BG_SOUND_H
