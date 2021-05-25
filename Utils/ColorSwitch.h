//
// Created by Benjam on 25-05-21.
//

#ifndef MATH4BG_COLORSWITCH_H
#define MATH4BG_COLORSWITCH_H


#include <glm/glm.hpp>

namespace Math4BG
{
    glm::vec3 MaskToFloat(uint32_t color);
    uint32_t Vec3ToMask(const glm::vec3 &color);
}


#endif //MATH4BG_COLORSWITCH_H
