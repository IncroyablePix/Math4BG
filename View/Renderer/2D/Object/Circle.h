//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_CIRCLE_H
#define MATH4BG_CIRCLE_H

#include "Object2D.h"
#include "Point.h"

namespace Math4BG
{
    class Circle : public Object2D
    {
    public:
        Circle();
        Circle(Point center, double radius, uint32_t color);
        ~Circle();
        void Draw(SDL_Surface* surface, const Point &size) override;

        Point m_center;
        double m_radius;

        /*void Draw(Renderer2D *renderer)
        {
            renderer->DrawEllipse(center.x, center.y, radius, radius, color);
        }*/
    };
}

#endif //MATH4BG_CIRCLE_H
