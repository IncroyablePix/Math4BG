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

    void Renderer2D::Draw(IDrawable *drawable)
    {
        ((Object2D*) drawable)->Draw(m_surface.get(), { (double) m_screen.width, (double) m_screen.height });
    }

    void Renderer2D::SwapBuffers()
    {
        SDL_RenderCopy(m_renderer.get(), m_texture.get(), nullptr, &m_screenRectangle);
        SDL_RenderPresent(m_renderer.get());
    }

    void Renderer2D::Clear()
    {
        /*int size = m_screen.width * m_screen.height;
        for (int i = 0; i < size; i++)
            ((uint32_t *) m_surface->pixels)[i] = 0x0;*/

        SDL_SetRenderDrawColor(m_renderer.get(), m_background.r, m_background.g, m_background.b, m_background.a);
        SDL_RenderClear(m_renderer.get());
        m_texture.reset(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()));
    }

    /*void Renderer2D::SetPixel(int x, int y, uint32_t argb)
    {
        int idx = y * m_screen.width + x;
        if (m_screen.size > idx && idx >= 0)
            ((uint32_t *) m_surface->pixels)[idx] = argb;
    }*/

/**
 * Draws a line on the screen in the desired colour.
 * Uses Bresenham's algorithm
 *
 * @param x0 Start x point
 * @param y0 Start ny point
 * @param x1 Finish x point
 * @param y1 Finish ny point
 * @param r Red factor
 * @param g Green factor
 * @param b Blue factor
 */
    /*void Renderer2D::DrawLine(int x0, int y0, int x1, int y1, uint32_t argb)
    {
        int x, y, dx, dy, adx, ady, d, d1, d2, step;

        ny(y0);
        ny(y1);

        dx = x1 - x0;
        adx = abs(dx);
        dy = y1 - y0;
        ady = abs(dy);

        if (adx == 0)
        {
            y = min(y0, y1);
            ady++;
            while (ady--)
            {
                SetPixel(x0, y++, argb);
            }

            return;
        }

        if (ady == 0)
        {
            x = min(x0, x1);
            adx++;
            while (adx--)
            {
                SetPixel(x++, y0, argb);
            }
        }

        if (adx < ady)
        {
            d = (adx << 1) - ady;
            d1 = adx << 1;
            d2 = (adx - ady) << 1;

            (y0 < y1) ? (x = x0, y = y0) : (x = x1, y = y1);
            step = ((sign(dx) == sign(dy)) ? 1 : -1);

            SetPixel(x, y, argb);

            while (ady--)
            {
                y++;
                if (d < 0)
                {
                    d += d1;
                } else
                {
                    x += step;
                    d += d2;
                }

                SetPixel(x, y, argb);
            }
        } else
        {
            d = (ady << 1) - adx;
            d1 = ady << 1;
            d2 = (ady - adx) << 1;
            (x0 < x1) ? (x = x0, y = y0) : (x = x1, y = y1);
            step = ((sign(dx) == sign(dy)) ? 1 : -1);

            SetPixel(x, y, argb);
            while (adx--)
            {
                x++;
                if (d < 0)
                {
                    d += d1;
                } else
                {
                    y += step;
                    d += d2;
                }

                SetPixel(x, y, argb);
            }
        }

        //m_screen.SetPixel(x0, y0, argb);
    }

    void Renderer2D::DrawEllipse(int x0, int y0, int xRadius, int yRadius, uint32_t argb)
    {
        ny(y0);
        float pi = 3.14159265358979323846264338327950288419716939937510;
        float pih = pi / 2.0; //half of pi

        const int prec = 27;
        float theta = 0;

        //starting point
        int x = (float) xRadius * cos(theta);
        int y = (float) yRadius * sin(theta);
        int x1 = x;
        int y1 = y;

        //repeat until theta >= 90;
        float step = pih / (float) prec;
        for (theta = step; theta <= pih; theta += step)
        {

            x1 = (float) xRadius * cosf(theta) + 0.5;
            y1 = (float) yRadius * sinf(theta) + 0.5;


            if ((x != x1) || (y != y1))
            {
                DrawLine(x0 + x, y0 - y, x0 + x1, y0 - y1, argb);
                DrawLine(x0 - x, y0 - y, x0 - x1, y0 - y1, argb);
                DrawLine(x0 - x, y0 + y, x0 - x1, y0 + y1, argb);
                DrawLine(x0 + x, y0 + y, x0 + x1, y0 + y1, argb);
            }

            x = x1;
            y = y1;
        }

        if (x != 0)
        {
            x = 0;
            DrawLine(x0 + x, y0 - y, x0 + x1, y0 - y1, argb);
            DrawLine(x0 - x, y0 - y, x0 - x1, y0 - y1, argb);
            DrawLine(x0 - x, y0 + y, x0 - x1, y0 + y1, argb);
            DrawLine(x0 + x, y0 + y, x0 + x1, y0 + y1, argb);
        }
    }

    void Renderer2D::DrawRect(int x0, int y0, int width, int height, uint32_t argb)
    {
        int x1, y1;
        ny(y0);
        x1 = x0 + width;
        y1 = y0 - height;

        if (x0 > x1)
            Swap(x1, x0);
        if (y0 > y1)
            Swap(y1, y0);

        for (int x = x0; x < x1; x++)
        {
            SetPixel(x, y0, argb);
            SetPixel(x, y1, argb);
        }

        for (int y = y0; y < y1; y++)
        {
            SetPixel(x0, y, argb);
            SetPixel(x1, y, argb);
        }
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
