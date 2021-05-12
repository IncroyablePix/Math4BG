//
// Created by Benjam on 15-04-21.
//

#include "Object2D.h"

namespace Math4BG
{
    Object2D::Object2D(uint32_t color) : m_color(color)
    {

    }

    void Object2D::SetPixel(SDL_Surface *surface, Point size, int x, int y)
    {
        int idx = y * size.x + x;
        if (size.x > x && x >= 0 && size.y > y && y >= 0 && idx >= 0)
            ((uint32_t *) surface->pixels)[idx] = m_color;
    }

    void Object2D::ny(int &y, const Point &size)
    {
        y = size.y - y;
    }

    void Object2D::SetColor(uint32_t color)
    {
        m_color = color;
    }
}