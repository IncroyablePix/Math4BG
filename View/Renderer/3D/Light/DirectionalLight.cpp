//
// Created by Benjam on 24-05-21.
//

#include "DirectionalLight.h"

namespace Math4BG
{
    DirectionalLight::DirectionalLight(const glm::vec3 &orientation, float intensity, const glm::vec3 &color) :
            Light({glm::vec3(0), glm::vec3(0.0), orientation, glm::vec3(1) }, color, intensity)
    {

    }
    DirectionalLight::DirectionalLight(const Transform &transform, float intensity, const glm::vec3 &color) :
            Light(transform, color, intensity)
    {

    }

    DirectionalLight::~DirectionalLight()
    = default;

    void DirectionalLight::ToShader(Math4BG::Shader &shader)
    {
        shader.SetUniformVec3("sDirectionalLight.Direction", m_transform.Rotation);
        shader.SetUniformVec4("sDirectionalLight.Color", glm::vec4(m_color, 1.0f));
        shader.SetUniform1f("sDirectionalLight.Intensity", m_intensity);
    }
}