//
// Created by Benjam on 15-04-21.
//

#include "Line.h"

#define		max(A,B)	((A) > (B) ? (A) : (B))
#define 	min(A,B)	((A) < (B) ? (A) : (B))
#define		sign(x)	((x < 0) ? 1 : 0)

namespace Math4BG
{
    Line::Line() :
    Object2D(0xFFFFFFFF)
    {

    }

    Line::Line(Point start, Point end, uint32_t color) :
    Object2D(color),
    m_start(start),
    m_end(end)
    {

    }

    Line::~Line()
    {

    }

    void Line::Draw(SDL_Surface* surface, const Point &size)
    {
        int x0 = m_start.x, y0 = m_start.y, x1 = m_end.x, y1 = m_end.y;
        int x, y, dx, dy, adx, ady, d, d1, d2, step;

        ny(y0, size);
        ny(y1, size);

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
                SetPixel(surface, size, x0, y++);
            }

            return;
        }

        if (ady == 0)
        {
            x = min(x0, x1);
            adx++;
            while (adx--)
            {
                SetPixel(surface, size, x++, y0);
            }
        }

        if (adx < ady)
        {
            d = (adx << 1) - ady;
            d1 = adx << 1;
            d2 = (adx - ady) << 1;

            (y0 < y1) ? (x = x0, y = y0) : (x = x1, y = y1);
            step = ((sign(dx) == sign(dy)) ? 1 : -1);

            SetPixel(surface, size, x, y);

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

                SetPixel(surface, size, x, y);
            }
        } else
        {
            d = (ady << 1) - adx;
            d1 = ady << 1;
            d2 = (ady - adx) << 1;
            (x0 < x1) ? (x = x0, y = y0) : (x = x1, y = y1);
            step = ((sign(dx) == sign(dy)) ? 1 : -1);

            SetPixel(surface, size, x, y);
            while (adx--)
            {
                x++;
                if (d < 0)
                {
                    d += d1;
                }
                else
                {
                    y += step;
                    d += d2;
                }

                SetPixel(surface, size, x, y);
            }
        }
    }
}