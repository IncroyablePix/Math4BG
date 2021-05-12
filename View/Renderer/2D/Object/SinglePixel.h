//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_SINGLEPIXEL_H
#define MATH4BG_SINGLEPIXEL_H

#include "Object2D.h"

namespace Math4BG
{
    class SinglePixel : public Object2D
    {
    public:
        SinglePixel();
        SinglePixel(Point position, uint32_t color);
        ~SinglePixel();
        void Draw(SDL_Surface* surface, const Point &size) override;

        void SetPosition(Point position);

    private:
        Point m_position;
    };
}

#endif //MATH4BG_SINGLEPIXEL_H
