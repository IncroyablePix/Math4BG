//
// Created by Benjam on 22-05-21.
//

#ifndef MATH4BG_LIGHT_H
#define MATH4BG_LIGHT_H

#include <glm/glm.hpp>
#include "../Shaders/Shader.h"
#include "../../../../Physics/Transform.h"

namespace Math4BG
{
    class Light
    {
    public:
        Light(const Transform &transform, glm::vec3 color, float intensity);
        virtual ~Light() = default;

        void SetPos(const glm::vec3 &pos);
        void SetOrigin(const glm::vec3 &position);
        void SetScale(const glm::vec3 &scale);
        void SetRotation(const glm::vec3 &rotation);

        virtual void ToShader(Shader &shader) = 0;

        void SetColor(const glm::vec3 &color);

    protected:
        Transform m_transform;
        float m_intensity;
        glm::vec3 m_color;
    };
}

#endif //MATH4BG_LIGHT_H
