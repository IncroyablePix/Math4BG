//
// Created by Benjam on 24-05-21.
//

#ifndef MATH4BG_DIRECTIONALLIGHT_H
#define MATH4BG_DIRECTIONALLIGHT_H

#include "Light.h"

namespace Math4BG
{
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight(const glm::vec3 &orientation, float intensity, const glm::vec3 &color);
        DirectionalLight(const Transform &transform, float intensity, const glm::vec3 &color);
        ~DirectionalLight() override;
        void ToShader(Shader &shader) override;
    };
}

#endif //MATH4BG_DIRECTIONALLIGHT_H
