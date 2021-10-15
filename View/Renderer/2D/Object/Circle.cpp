//
// Created by Benjam on 15-04-21.
//

#include "Circle.h"
#include "Line.h"
#include "../../../../Utils/ColorSwitch.h"
#include <cmath>

namespace Math4BG
{
    Circle::Circle() : Object2D()
    {

    }

    Circle::Circle(std::shared_ptr<Shader> shader, glm::vec3 center, double radius, uint32_t color) :
    Object2D(shader, &model, { center }, MaskToFloat(color)),
    m_center(center),
    m_radius(radius)
    {

    }

    Circle::~Circle()
    {

    }

    /*void Circle::Draw(SDL_Surface *surface, const Point &size)
    {
        int x0 = m_center.x, y0 = m_center.y;
        double xRadius = m_radius, yRadius = m_radius;

        std::vector<Line> lines;

        ny(y0, size);
        double pi = 3.14159265358979323846264338327950288419716939937510;
        double pih = pi / 2.0; //half of pi

        const int prec = 27;
        double theta = 0;

        //starting point
        double x = (double) xRadius * cos(theta);
        double y = (double) yRadius * sin(theta);
        double x1 = x;
        double y1 = y;

        //repeat until theta >= 90;
        double step = pih / (double) prec;
        for (theta = step; theta <= pih; theta += step)
        {

            x1 = (double) xRadius * cos(theta) + 0.5;
            y1 = (double) yRadius * sin(theta) + 0.5;


            if ((x != x1) || (y != y1))
            {
                lines.push_back({ {x0 + x, y0 - y}, {x0 + x1, y0 - y1}, m_color });
                lines.push_back({ {x0 + x, y0 - y}, {x0 + x1, y0 - y1}, m_color });
                lines.push_back({ {x0 - x, y0 - y}, {x0 - x1, y0 - y1}, m_color });
                lines.push_back({ {x0 - x, y0 + y}, {x0 - x1, y0 + y1}, m_color });
                lines.push_back({ {x0 + x, y0 + y}, {x0 + x1, y0 + y1}, m_color });
            }

            x = x1;
            y = y1;
        }

        if (x != 0)
        {
            x = 0;
            lines.push_back({ { x0 + x, y0 - y }, { x0 + x1, y0 - y1 }, m_color });
            lines.push_back({ { x0 - x, y0 - y }, { x0 - x1, y0 - y1 }, m_color });
            lines.push_back({ { x0 - x, y0 + y }, { x0 - x1, y0 + y1 }, m_color });
            lines.push_back({ { x0 + x, y0 + y }, { x0 + x1, y0 + y1 }, m_color });
        }

        for(Line l : lines)
            l.Draw(surface, size);
    }*/
}