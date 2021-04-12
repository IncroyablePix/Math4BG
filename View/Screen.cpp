//
// Created by Benjam on 11-04-21.
//

#include <stdexcept>
#include "Screen.h"

Screen::Screen(unsigned int w, unsigned int h) : width(w), height(h), size(w * h), m_data(new Pixel[w * h])
{
}

Screen::~Screen()
{
    delete[] m_data;
}

void Screen::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    SetPixel(x, y, r, g, b, (r == 0x0 && g == 0x0 && b == 0x0) ? 0x0 : 0xFF);
}

Pixel& Screen::operator[](int index)
{
    if(index >= width * height)
        throw std::runtime_error("Out of bounds array exception !");

    return m_data[index];
}

void Screen::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if(!(x < 0 || x >= width || y < 0 || y >= height))
        (*this)[y * width + x] = { r, g, b, a };
}
