//
// Created by Benjam on 16-04-21.
//

#include "Rectangle.h"

namespace Math4BG
{
    Rectangle::Rectangle() :
    Object2D(0xFFFFFFFF)
    {

    }

    Rectangle::Rectangle(Math4BG::Point position, int width, int height, uint32_t color) :
    Object2D(color),
    m_start(position),
    m_width(width),
    m_height(height)
    {

    }

    Rectangle::~Rectangle()
    {

    }

    void Rectangle::Draw(SDL_Surface *surface, const Math4BG::Point &size)
    {
        int x0 = m_start.x, y0 = m_start.y;
        int x1, y1;
        x1 = x0 + m_width;
        y1 = y0 + m_height;

        if (x0 > x1)
            Swap(x1, x0);
        if (y0 > y1)
            Swap(y1, y0);

        for (int x = x0; x < x1; x++)
        {
            SetPixel(surface, size, x, size.y - y0);
            SetPixel(surface, size, x, size.y - y1);
        }

        for (int y = y0; y < y1; y++)
        {
            SetPixel(surface, size, x0, size.y - y);
            SetPixel(surface, size, x1, size.y - y);
        }
    }
}