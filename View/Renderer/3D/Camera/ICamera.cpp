//
// Created by Benjam on 13-05-21.
//

#include "ICamera.h"

namespace Math4BG
{
    ICamera::ICamera(const glm::mat4& projection) : m_projection(projection)
    {

    }

    void ICamera::SetCameraPos(const glm::vec3 &position)
    {
        m_eye = position;
    }
}