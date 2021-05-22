//
// Created by Benjam on 22-05-21.
//

#include "Light.h"

namespace Math4BG
{
    Light::Light(const Transform& transform, glm::vec3 color, float intensity) :
    m_transform(transform),
    m_color(color),
    m_intensity(intensity)
    {

    }

    void Light::SetPos(const glm::vec3 &pos)
    {
        m_transform.Position = pos;
    }

    void Light::SetOrigin(const glm::vec3 &position)
    {
        m_transform.Origin = position;
    }

    void Light::SetScale(const glm::vec3 &scale)
    {
        m_transform.Scale = scale;
    }

    void Light::SetRotation(const glm::vec3 &rotation)
    {
        m_transform.Rotation = rotation;
    }

    void Light::SetColor(const glm::vec3 &color)
    {
        m_color = color;
    }
}