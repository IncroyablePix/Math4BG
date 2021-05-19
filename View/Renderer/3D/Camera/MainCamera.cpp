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

    m_eye(0.0f, 0.0f, 0.0f),
    m_view(0.0f, 0.0f, -1.0f),
    m_up(0.0f, 1.0f, 0.0f),
    m_speed(25.0f),

    ICamera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
    {
        UpdatePosition();
        UpdateView();
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
        //return glm::lookAt(m_eye, m_view, m_up);
        return GetProjectionMatrix() * GetView() * glm::mat4(1.0f);
    }

    glm::mat4 MainCamera::GetView() {
        return glm::lookAt(m_eye, m_view, glm::vec3(0.0f, 1.0f, 0.0f));
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

        glm::quat orientation = m_direction;
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_eye) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);
    }

    glm::vec3 MainCamera::CalculatePosition() const
    {
        return (m_focalPoint - (Forward() * m_distance));
    }

    void MainCamera::Move(glm::vec3 direction, float fBy)
    {
        direction *= fBy;

        m_eye += direction;
        m_view += direction;
        //UpdatePosition();
    }

    float RadToDeg(float rad)
    {
        return rad * (180 / 3.14f);
    }

    void MainCamera::Update(double lag)
    {
        if(Mouse.Down(MouseButton::LMB))
        {
            std::cout << "Mouse delta : " << Mouse.DeltaPosition().x << ", " << Mouse.DeltaPosition().x << std::endl;

            m_horizontalAngle += (0.25f * lag * (-Mouse.DeltaPosition().x));
            m_verticalAngle += (0.25f * lag * (-Mouse.DeltaPosition().y));

            m_direction = {cos(m_verticalAngle) * sin(m_horizontalAngle),
                           sin(m_verticalAngle),
                           cos(m_verticalAngle) * cos(m_horizontalAngle)};

            m_view += m_direction;
        }

        //---

        glm::vec3 dir = {0.0, 0.0, 0.0f};

        if(Keys.Down(KeyButton::Z))
            dir += Forward();
        if(Keys.Down(KeyButton::S))
            dir = Backward();
        if(Keys.Down(KeyButton::Q))
            dir += Left();
        if(Keys.Down(KeyButton::D))
            dir += Right();

        //std::cout << "Pos : " << m_eye.x << ", " << m_eye.y << ", " << m_eye.z << std::endl;
        std::cout << "Rot : " << RadToDeg(m_horizontalAngle) << ", " << RadToDeg(m_verticalAngle) << std::endl;
        std::cout << "Dir : " << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << std::endl;

        Move(dir * m_speed, lag);

        //UpdateView();
    }
}