//
// Created by Benjam on 25-05-21.
//

#include "ColorSwitch.h"

namespace Math4BG
{
    // A R G B Mask !
    glm::vec3 MaskToFloat(uint32_t color)
    {
        uint8_t r = color >> 16;
        uint8_t g = color >> 8;
        uint8_t b = color;

        return {(float) (r & 0xFF) / (float) 0xFF,
                (float) (g & 0xFF) / (float) 0xFF,
                (float) (b & 0xFF) / (float) 0xFF};
    }

    uint32_t Vec3ToMask(const glm::vec3 &color)
    {
        uint8_t r = color.x * 0xFF;
        uint8_t g = color.y * 0xFF;
        uint8_t b = color.z * 0xFF;

        return 0xFF000000 | (r << 16) | (g << 8) | (b);
    }
}