//
// Created by Benjam on 13-04-21.
//

#include "IRenderer.h"


namespace Math4BG
{
    IRenderer::IRenderer(SDL_Window *window, unsigned int width, unsigned int height) :
            m_screen(width, height),
            m_background{0x0, 0x0, 0x0, 0xFF}
    {

    }

    IRenderer::~IRenderer()
    = default;

    void IRenderer::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
    {
        m_background.r = r;
        m_background.g = g;
        m_background.b = b;
    }
}