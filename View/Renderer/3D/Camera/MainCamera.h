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

        glm::mat4 GetView();

        const glm::vec3 &GetPos();

    private:
        //--- Directions ---//
        glm::vec3 m_up;
        glm::vec3 m_bottom;
        glm::vec3 m_left;
        glm::vec3 m_right;
        glm::vec3 m_forward;
        glm::vec3 m_backward;

        float m_speed = 5.0f;

        float m_horizontalAngle = 0.0f;
        float m_verticalAngle = 0.0f;

        glm::vec3 m_view;

        glm::mat4 m_modelToCamera;

        void UpdatePosition();

        void UpdateDirection();

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
