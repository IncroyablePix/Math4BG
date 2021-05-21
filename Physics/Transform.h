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
        Transform(const glm::vec3 &position)
                : Position(position), Origin(glm::vec3(0.f)), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f))
        { }
        Transform(const glm::vec3 &position, const glm::vec3 &origin, const glm::vec3 &rotation, const glm::vec3 &scale)
                : Position(position), Origin(origin), Rotation(rotation), Scale(scale)
        { }
        Transform()
                : Position(glm::vec3(0.0f)), Origin(glm::vec3(0.f)), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f))
        { }

        glm::vec3 Position;
        glm::vec3 Origin;
        glm::vec3 Rotation;
        glm::vec3 Scale;

        Transform operator+(const Transform &t1);
    };
}

#endif //MATH4BG_TRANSFORM_H
