//
// Created by Benjam on 13-05-21.
//

#include "ICamera.h"
#include "MainCamera.h"

namespace Math4BG
{
    ICamera::ICamera(float width, float height, float fov, float nearClip, float farClip) :
    m_width(width),
    m_height(height),
    m_nearClip(nearClip),
    m_farClip(farClip),
    m_FOV(fov)
    {
        m_projection = (glm::perspective(glm::radians(fov), width / height, nearClip, farClip));
    }

    void ICamera::SetCameraPos(const glm::vec3 &position)
    {
        m_eye = position;
    }

    void ICamera::SetCameraRot(const glm::vec2 &rot)
    {
        m_horizontalAngle = rot.x;
        m_verticalAngle = rot.y;
        UpdateDirection();
        //m_view = position;
    }

    void ICamera::SetViewportSize(float width, float height)
    {
        m_width = width;
        m_height = height;

        UpdateProjection();
    }

    void ICamera::UpdateProjection()
    {
        m_projection = glm::perspective(glm::radians(m_FOV), m_width / m_height, m_nearClip, m_farClip);
    }

    void ICamera::UpdateDirection()
    {
        const glm::vec3 top = glm::vec3(0.f, 1.f, 0.f);

        m_forward =
        {
                cos(glm::radians(m_horizontalAngle) * cos(glm::radians(m_verticalAngle))),
                sin(glm::radians(m_verticalAngle)),
                sin(glm::radians(m_horizontalAngle)) * cos(glm::radians(m_verticalAngle))
        };
        m_forward = glm::normalize(m_forward);
        m_backward = -m_forward;

        //----

        m_right = glm::normalize(glm::cross(m_forward, top));
        m_left = -m_right;

        //---

        m_up = glm::normalize(glm::cross(m_right, m_forward));
    }

    void ICamera::UpdatePosition()
    {
        m_modelToCamera = glm::translate(glm::mat4(1.0), m_eye);
        m_modelToCamera = glm::scale(m_modelToCamera, glm::vec3(8.0f, 8.0f, 8.0f));
    }

    void ICamera::UpdateView()
    {
        m_eye = CalculatePosition();

        glm::quat orientation = m_forward;
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_eye) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);
    }

    glm::vec3 ICamera::CalculatePosition() const
    {
        return (m_focalPoint - (m_forward * m_distance));
    }
}