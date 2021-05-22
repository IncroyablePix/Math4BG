//
// Created by Benjam on 22-05-21.
//

#include "PointLight.h"

namespace Math4BG
{
    PointLight::PointLight(const Math4BG::Transform &transform, float intensity, const glm::vec3 &color, float constant, float linear, float quadratic) :
    m_constant(constant),
    m_linear(linear),
    m_quadratic(quadratic),

    Light(transform, color, intensity)
    {

    }

    PointLight::PointLight(const Math4BG::Transform &transform, float intensity, const glm::vec3 &color) :
    m_constant(1.0f),
    m_linear(0.05f),
    m_quadratic(0.0075f),

    Light(transform, color, intensity)
    {

    }

    PointLight::~PointLight()
    = default;

    void PointLight::ToShader(Shader &shader)
    {
        shader.SetUniformVec3("sPointLight.Position", m_transform.Position);
        shader.SetUniform1f("sPointLight.Intensity", m_intensity);
        shader.SetUniformVec4("sPointLight.Color", glm::vec4(m_color, 1.0f));

        shader.SetUniform1f("sPointLight.Constant", m_constant);
        shader.SetUniform1f("sPointLight.Linear", m_linear);
        shader.SetUniform1f("sPointLight.Quadratic", m_quadratic);
    }
}