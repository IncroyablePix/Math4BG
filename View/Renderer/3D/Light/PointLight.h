//
// Created by Benjam on 22-05-21.
//

#ifndef MATH4BG_POINTLIGHT_H
#define MATH4BG_POINTLIGHT_H


#include "Light.h"
#include "../../../../Physics/Transform.h"

namespace Math4BG
{
    class PointLight : public Light
    {
    public:
        PointLight(const Transform &transform, float intensity, const glm::vec3 &color, float constant, float linear, float quadratic);
        PointLight(const Transform &transform, float intensity, const glm::vec3 &color);
        ~PointLight() override;
        void ToShader(Shader &shader) override;

    protected:
        float m_linear;
        float m_quadratic;
        float m_constant;
    };
}

#endif //MATH4BG_POINTLIGHT_H
