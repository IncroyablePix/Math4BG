//
// Created by Benjam on 13-05-21.
//

#include "MainCamera.h"

namespace Math4BG {

    MainCamera::MainCamera(float fov, float width, float height, float nearClip, float farClip) :
    m_aspectRatio((float) width / (float) height),
    ICamera(width, height, fov, nearClip, farClip)
    {
        UpdatePosition();
        UpdateView();
        UpdateDirection();
    }

    void MainCamera::Move(glm::vec3 direction, float fBy)
    {
        direction *= fBy;

        m_eye += direction;
        m_view += direction;
    }

    void MainCamera::Update(const MouseInput &mouse, const KeyInput &keys, double lag)
    {
        if(mouse.Down(MouseButton::LMB))
        {
            m_horizontalAngle += lag * m_speed * 2 * static_cast<float>(mouse.DeltaPosition().x);
            m_verticalAngle -= lag * m_speed * 2 * static_cast<float>(mouse.DeltaPosition().y);

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

        if(keys.Down(KeyButton::Z))
            dir += m_forward;
        if(keys.Down(KeyButton::S))
            dir += m_backward;
        if(keys.Down(KeyButton::Q))
            dir += m_left;
        if(keys.Down(KeyButton::D))
            dir += m_right;

        Move(dir * m_speed, lag);
    }
}