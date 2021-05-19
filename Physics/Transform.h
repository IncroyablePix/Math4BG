//
// Created by Benjam on 19-05-21.
//

#ifndef MATH4BG_TRANSFORM_H
#define MATH4BG_TRANSFORM_H

#include <glm/glm.hpp>

namespace Math4BG
{
    struct Transform
    {
        Transform(const glm::vec3 &position) : Position(position) { }

        glm::vec3 Position;
    };
}

#endif //MATH4BG_TRANSFORM_H
