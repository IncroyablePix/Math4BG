//
// Created by Benjam on 24-05-21.
//

#include "WAVSound.h"

namespace Math4BG
{
    WAVSound::WAVSound(const std::string &path)
    {
        if(SDL_LoadWAV(path.c_str(), &m_wavSpec, &m_buffer, &m_length) == nullptr)
            throw std::runtime_error("Sound could not be found!");

        m_wavSpec.callback = WAVSound::ForwardCallback;
        m_wavSpec.userdata = this;
    }

    WAVSound::~WAVSound()
    {
        SDL_FreeWAV(m_buffer);
    }

    void WAVSound::Play()
    {
        SDL_PauseAudio(0);
    }

    void WAVSound::Pause()
    {
    }

    void WAVSound::Stop()
    {

    }

    void WAVSound::BufferStreamCallback(uint8_t* stream, int len)
    {
        if(m_audioLen == 0)
            return;

        len = (len > m_audioLen) ? m_audioLen : len;
        SDL_MixAudio(stream, m_audioPos, len, SDL_MIX_MAXVOLUME);

        m_audioPos += len;
        m_audioLen -= len;
    }
}