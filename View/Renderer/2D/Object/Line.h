//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_LINE_H
#define MATH4BG_LINE_H

#include "Object2D.h"
#include "Point.h"

namespace Math4BG
{
    class Line : public Object2D
    {
    public:
        Line();
        Line(Point start, Point end, uint32_t color);
        ~Line();
        void Draw(SDL_Surface* surface, const Point &size) override;

        Point m_start;
        Point m_end;

        /*void Draw(Renderer2D *renderer)
        {
            renderer->DrawLine(start.x, start.y, end.x, end.y, color);
        }*/
    };
}

#endif //MATH4BG_LINE_H
