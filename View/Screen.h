//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_SCREEN_H
#define ARCPOSITION_SCREEN_H

#include <vector>
#include <cstdint>


namespace Math4BG
{
    struct Pixel
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    class Screen
    {
    public:
        Screen(unsigned int w, unsigned int h);

        ~Screen();

        void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

        void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        const int width = 0;
        const int height = 0;
        const int size = 0;

        Pixel &operator[](int index);

    private:
        Pixel *m_data;
    };
}

#endif //ARCPOSITION_SCREEN_H
