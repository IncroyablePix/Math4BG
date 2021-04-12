//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_SHAPES_H
#define ARCPOSITION_SHAPES_H

#include "../View/Renderer.h"


#define CIRCLE_COLOR 						(0x4E8EB9FF)
#define LINE_COLOR                       	(0xFF0000FF)

struct Point
{
    double x;
    double y;
};

struct Circle
{
    Point center;
    double radius;
    uint32_t color;

    void Draw(Renderer* renderer)
    {
        renderer->DrawEllipse(center.x, center.y, radius, radius, color);
    }
};

struct Line
{
    Point start;
    Point end;
    uint32_t color;

    void Draw(Renderer* renderer)
    {
        renderer->DrawLine(start.x, start.y, end.x, end.y, color);
    }
};


#endif //ARCPOSITION_SHAPES_H
