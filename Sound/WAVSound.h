//
// Created by Benjam on 24-05-21.
//

#ifndef MATH4BG_WAVSOUND_H
#define MATH4BG_WAVSOUND_H

#include "Sound.h"

namespace Math4BG
{
    class WAVSound : public Sound
    {
    public:
        WAVSound(const std::string &path);
        ~WAVSound() override;

        void Play() override;
        void Pause() override;
        void Stop() override;

    private:
        void BufferStreamCallback(uint8_t* stream, int len);
        uint8_t* m_audioPos;
        uint32_t m_audioLen;

        uint8_t* m_buffer;
        SDL_AudioSpec m_wavSpec;

        inline static void ForwardCallback(void* audioData, uint8_t* stream, int len)
        {
            static_cast<WAVSound*>(audioData)->BufferStreamCallback(stream, len);
        }
    };
}

#endif //MATH4BG_WAVSOUND_H
