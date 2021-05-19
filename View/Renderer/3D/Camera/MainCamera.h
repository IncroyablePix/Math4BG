//
// Created by Benjam on 13-05-21.
//

#ifndef MATH4BG_MAINCAMERA_H
#define MATH4BG_MAINCAMERA_H

#include "ICamera.h"
#include <glm/gtx/quaternion.hpp>

namespace Math4BG
{
    class MainCamera : public ICamera
    {
    public:
        MainCamera() = default;
        MainCamera(float fov, float aspectRatio, float nearClip, float farClip);

        const glm::mat4 GetProjectionMatrix() override;
        const glm::mat4 GetModelViewMatrix() override;
        const glm::mat4 GetNormalMatrix() override;

        void Update(double lag);

        void Move(glm::vec3 direction, float fBy);

        void SetViewportSize(float width, float height);

        const glm::mat4 GetMVP() override;

        /*inline glm::vec3 Forward() const
        {
            return m_view - m_eye;
        }*/

        inline glm::vec3 Up() const{ return glm::vec3(0.0f, 1.0f, 0.0f); } // y + 1 - UP
        inline glm::vec3 Down() const{ return glm::vec3(0.0f, -1.0f, 0.0f); } // y - 1 - DOWN

        inline glm::vec3 Right() const { return {sin(m_horizontalAngle - 3.14f / 2.0f), 0.0f, cos(m_horizontalAngle - 3.14f / 2.0f) }; }// z + 1 - FORWARD
        inline glm::vec3 Left() const { return {sin(m_horizontalAngle + 3.14f / 2.0f), 0.0f, cos(m_horizontalAngle + 3.14f / 2.0f) }; }// z - 1 - BACKWARDS

        inline glm::vec3 Forward() const { return m_direction; } // x - 1 - LEFT
        inline glm::vec3 Backward() const { return -m_direction; } // x + 1 - RIGHT

    private:
        float m_speed = 5.0f;

        float m_horizontalAngle = 3.14f; // pi
        float m_verticalAngle = 0.0f;

        glm::vec3 m_direction = {cos(m_verticalAngle) * sin(m_horizontalAngle),
                                   sin(m_verticalAngle),
                                 cos(m_verticalAngle) * cos(m_horizontalAngle) };

        glm::vec3 m_eye;
        glm::vec3 m_view;
        glm::vec3 m_up;
        float m_pitch = 0.0f;
        float m_yaw = 0.0f;

        glm::mat4 m_modelToCamera;
        glm::mat4 GetView();

        void UpdatePosition();


        void UpdateProjection();
        void UpdateView();
        glm::vec3 CalculatePosition() const;

        float m_FOV = 45.0f;
        float m_aspectRatio = 1.778f;

        //---Clipping---//
        float m_nearClip = 0.1f;
        float m_farClip = 1000.0f;

        glm::mat4 m_viewMatrix;
        glm::vec3 m_focalPoint;

        float m_distance;
        float m_width = 1280, m_height = 720;
    };
}

#endif //MATH4BG_MAINCAMERA_H
