//
// Created by Benjam on 15-04-21.
//

#include "SinglePixel.h"

namespace Math4BG
{
    SinglePixel::SinglePixel() :
            Object2D(0xFFFFFFFF)
    {

    }

    SinglePixel::SinglePixel(Math4BG::Point position, uint32_t color) :
            Object2D(color),
            m_position(position)
    {

    }

    void SinglePixel::SetPosition(Point position)
    {
        m_position = position;
    }

    SinglePixel::~SinglePixel()
    = default;

    void SinglePixel::Draw(SDL_Surface *surface, const Math4BG::Point &size)
    {
        SetPixel(surface, size, m_position.x, m_position.y);
    }
}