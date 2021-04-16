//
// Created by Benjam on 16-04-21.
//

#ifndef MATH4BG_RECTANGLE_H
#define MATH4BG_RECTANGLE_H


#include "Point.h"
#include "Object2D.h"

namespace Math4BG
{
    class Rectangle : public Object2D
    {
    public:
        Rectangle();
        Rectangle(Point position, int width, int height, uint32_t color);
        ~Rectangle();

        void Draw(SDL_Surface* surface, const Point &size) override;

        Point m_start;
        int m_height;
        int m_width;

    private:
        template<typename T>
        void Swap(T &a, T &b)
        {
            T temp = a;
            a = b;
            b = temp;
        }
    };
}

#endif //MATH4BG_RECTANGLE_H
