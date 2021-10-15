//
// Created by Benjam on 13-05-21.
//

#ifndef MATH4BG_ICAMERA_H
#define MATH4BG_ICAMERA_H

#include <glm/glm.hpp>

namespace Math4BG
{
    class ICamera
    {
    public:
        ICamera() = default;
        ICamera(float width, float height, float fov, float nearClip, float farClip);
        virtual ~ICamera() = default;

        const glm::mat4 GetMVP() const;
        const glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetView() const;

        const glm::vec3 &GetPos() const;

        void SetCameraPos(const glm::vec3 &position);
        void SetCameraRot(const glm::vec2 &rot);

        void SetViewportSize(float width, float height);

        inline const glm::vec3 Up() { return m_up; }
        inline const glm::vec3 Down() { return m_bottom; }
        inline const glm::vec3 Forward() { return m_forward; }
        inline const glm::vec3 Backward() { return m_backward; }
        inline const glm::vec3 Right() { return m_right; }
        inline const glm::vec3 Left() { return m_left; }

        glm::vec2 GetPixelSize() { return { 1.0f / m_width, 1.0f / m_height }; }

    protected:
        void UpdateDirection();
        void UpdateProjection();
        void UpdatePosition();
        void UpdateView();
        glm::vec3 CalculatePosition() const;

        //--- Directions ---//
        glm::vec3 m_up;
        glm::vec3 m_bottom;
        glm::vec3 m_left;
        glm::vec3 m_right;
        glm::vec3 m_forward;
        glm::vec3 m_backward;

        glm::mat4 m_projection = glm::mat4(1.0f);
        glm::vec3 m_eye = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_view = glm::vec3(0.0f, 0.0f, 0.0f);
        float m_distance;

        glm::mat4 m_modelToCamera;
        glm::mat4 m_viewMatrix;
        glm::vec3 m_focalPoint;

        float m_horizontalAngle = 0.0f;
        float m_verticalAngle = 0.0f;

        float m_FOV = 45.0f;
        float m_nearClip = 0.1f;
        float m_farClip = 1000.0f;

        float m_width;
        float m_height;
    };
}

#endif //MATH4BG_ICAMERA_H
