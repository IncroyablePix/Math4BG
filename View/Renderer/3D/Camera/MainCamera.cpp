//
// Created by Benjam on 13-05-21.
//

#include <iostream>
#include "MainCamera.h"
#include "ICamera.h"
#include "../../../../Input/MouseInput.h"
#include "../../../../Input/KeyInput.h"

namespace Math4BG {

    MainCamera::MainCamera(float fov, float width, float height, float nearClip, float farClip) :
    m_aspectRatio((float) width / (float) height),
    ICamera(width, height, fov, nearClip, farClip)
    {
        UpdatePosition();
        UpdateView();
        UpdateDirection();
    }

    const glm::mat4 MainCamera::GetProjectionMatrix()
    {
        return m_projection;
    }

    const glm::mat4 MainCamera::GetMVP()
    {
        return GetProjectionMatrix() * GetView() * glm::mat4(1.0f);
    }

    glm::mat4 MainCamera::GetView()
    {
        return glm::lookAt(m_eye, m_eye + m_forward, m_up);
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

    const glm::vec3 &MainCamera::GetPos()
    {
        return m_eye;
    }
}