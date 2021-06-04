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
        MainCamera(float fov, float width, float height, float nearClip, float farClip);

        const glm::mat4 GetProjectionMatrix() override;

        void Update(double lag);

        void Move(glm::vec3 direction, float fBy);

        const glm::mat4 GetMVP() override;

        glm::mat4 GetView();

        const glm::vec3 &GetPos();

    private:
        float m_speed = 5.0f;

        float m_aspectRatio = 1.778f;
    };
}

#endif //MATH4BG_MAINCAMERA_H
