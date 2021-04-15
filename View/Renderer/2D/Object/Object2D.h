//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_OBJECT2D_H
#define MATH4BG_OBJECT2D_H

#include <cstdint>
#include <SDL2/SDL.h>
#include "Point.h"
#include "../../Draw/IDrawable.h"

namespace Math4BG
{
    class Object2D : public IDrawable
    {
    public:
        Object2D(uint32_t color);
        ~Object2D() override = default;
        virtual void Draw(SDL_Surface* surface, const Point &size) = 0;
        void SetColor(uint32_t color);

    protected:
        uint32_t m_color;

        void SetPixel(SDL_Surface* surface, Point size, int x, int y);
        static void ny(int &y, const Point &size);
    };
}

#endif //MATH4BG_OBJECT2D_H
