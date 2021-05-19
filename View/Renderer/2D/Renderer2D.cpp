//
// Created by Benjam on 11-04-21.
//

#include <cmath>
#include <iostream>
#include "Renderer2D.h"
#include "Object/Object2D.h"

#define		max(A,B)	((A) > (B) ? (A) : (B))
#define 	min(A,B)	((A) < (B) ? (A) : (B))
#define		sign(x)	((x < 0) ? 1 : 0)


namespace Math4BG
{
    Renderer2D::Renderer2D(SDL_Window *window, unsigned int width, unsigned int height)
            : IRenderer(window, width, height),
              m_renderer(nullptr, SDL_DestroyRenderer),
              m_texture(nullptr, SDL_DestroyTexture),
              m_surface(nullptr, SDL_FreeSurface),
              m_screenRectangle{0, 0}
    {
        m_renderer.reset(SDL_CreateRenderer(window, -1, 0));
        Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        m_screenRectangle.w = width;
        m_screenRectangle.h = height;

        m_surface.reset(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask));
    }

    Renderer2D::~Renderer2D()
    = default;

    void Renderer2D::Draw(MainCamera *camera, IDrawable *drawable)
    {
        ((Object2D*) drawable)->Draw(m_surface.get(), { (double) m_screen.width, (double) m_screen.height });
    }

    void Renderer2D::SwapBuffers()
    {
        SDL_SetRenderDrawColor(m_renderer.get(), m_background.r, m_background.g, m_background.b, m_background.a);
        SDL_RenderClear(m_renderer.get());
        m_texture.reset(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()));
        SDL_RenderCopy(m_renderer.get(), m_texture.get(), nullptr, &m_screenRectangle);
        SDL_RenderPresent(m_renderer.get());
    }

    void Renderer2D::Clear()
    {
        /*int size = m_screen.width * m_screen.height;
        for (int i = 0; i < size; i++)
            ((uint32_t *) m_surface->pixels)[i] = 0x000000FF;*/
        Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif
        m_surface.reset(SDL_CreateRGBSurface(SDL_SWSURFACE, m_screen.width, m_screen.height, 32, rmask, gmask, bmask, amask));
    }

    /*void Renderer2D::SetPixel(int x, int y, uint32_t argb)
    {
        int idx = y * m_screen.width + x;
        if (m_screen.size > idx && idx >= 0)
            ((uint32_t *) m_surface->pixels)[idx] = argb;
    }

    void Renderer2D::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t argb)
    {
        ny(y0);
        ny(y1);
        ny(y2);

        DrawLine(x0, y0, x1, y1, argb);
        DrawLine(x1, y1, x2, y2, argb);
        DrawLine(x0, y0, x2, y2, argb);
    }*/

    void Renderer2D::ny(int &y)
    {
        y = Height() - y;
    }

    std::shared_ptr<Renderer2D> Renderer2D::Create(SDL_Window *window, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<Renderer2D>(static_cast<Renderer2D *>(new Renderer2D(window, width, height)));
    }
}
