//
// Created by Benjam on 13-05-21.
//

#include <iostream>
#include "MainCamera.h"
#include "ICamera.h"
#include "../../../../Input/MouseInput.h"
#include "../../../../Input/KeyInput.h"

namespace Math4BG {

    MainCamera::MainCamera(float fov, float aspectRatio, float nearClip, float farClip) :
    m_FOV(fov),
    m_aspectRatio(aspectRatio),
    m_nearClip(nearClip),
    m_farClip(farClip),

    m_view(0.0f, 0.0f, -1.0f),

    ICamera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
    {
        UpdatePosition();
        UpdateView();
        UpdateDirection();
    }

    const glm::mat4 MainCamera::GetProjectionMatrix()
    {
        return m_projection;
    }

    const glm::mat4 MainCamera::GetModelViewMatrix()
    {
        return GetMVP() * m_modelToCamera;
        //return m_viewMatrix;
    }

    const glm::mat4 MainCamera::GetNormalMatrix()
    {
        return glm::transpose(glm::inverse(m_modelToCamera));
    }

    const glm::mat4 MainCamera::GetMVP()
    {
        return GetProjectionMatrix() * GetView() * glm::mat4(1.0f);
    }

    glm::mat4 MainCamera::GetView()
    {
        return glm::lookAt(m_eye, m_eye + m_forward, m_up);
    }

    void MainCamera::UpdatePosition()
    {
        m_modelToCamera = glm::translate(glm::mat4(1.0), m_eye);
        m_modelToCamera = glm::scale(m_modelToCamera, glm::vec3(8.0f, 8.0f, 8.0f));
    }

    void MainCamera::SetViewportSize(float width, float height)
    {
        m_width = width;
        m_height = height;

        UpdateProjection();
    }

    void MainCamera::UpdateProjection()
    {
        m_projection = glm::perspective(glm::radians(m_FOV), m_width / m_height, m_nearClip, m_farClip);
    }

    void MainCamera::UpdateView()
    {
        m_eye = CalculatePosition();

        glm::quat orientation = m_forward;
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_eye) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);
    }

    glm::vec3 MainCamera::CalculatePosition() const
    {
        return (m_focalPoint - (m_forward * m_distance));
    }

    void MainCamera::Move(glm::vec3 direction, float fBy)
    {
        direction *= fBy;

        m_eye += direction;
        m_view += direction;
    }

    void MainCamera::Update(double lag)
    {
        if(Mouse.Down(MouseButton::LMB))
        {
            m_horizontalAngle += lag * m_speed * 2 * static_cast<float>(Mouse.DeltaPosition().x);
            m_verticalAngle -= lag * m_speed * 2 * static_cast<float>(Mouse.DeltaPosition().y);

            //---

            if(m_verticalAngle > 80.0f)
                m_verticalAngle = 80.0f;
            else if(m_verticalAngle < -80.0f)
                m_verticalAngle = -80.0f;

            //---

            if(m_horizontalAngle > 360.0f || m_horizontalAngle < -360.0f)
                m_horizontalAngle = 0.0f;

            UpdateDirection();
        }

        //---

        glm::vec3 dir = {0.0, 0.0, 0.0f};

        if(Keys.Down(KeyButton::Z))
            dir += m_forward;
        if(Keys.Down(KeyButton::S))
            dir += m_backward;
        if(Keys.Down(KeyButton::Q))
            dir += m_left;
        if(Keys.Down(KeyButton::D))
            dir += m_right;

        Move(dir * m_speed, lag);
    }

    void MainCamera::UpdateDirection()
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

    const glm::vec3 &MainCamera::GetPos()
    {
        return m_eye;
    }
}