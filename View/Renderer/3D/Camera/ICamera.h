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
        ICamera(const glm::mat4& projection);
        virtual ~ICamera() = default;

        virtual const glm::mat4 GetMVP() = 0;
        virtual const glm::mat4 GetProjectionMatrix() = 0;
        virtual const glm::mat4 GetModelViewMatrix() = 0;
        virtual const glm::mat4 GetNormalMatrix() = 0;

        void SetCameraPos(const glm::vec3 &position);

    protected:
        glm::mat4 m_projection = glm::mat4(1.0f);
        glm::vec3 m_eye = glm::vec3(0.0f, 0.0f, 0.0f);
    };
}

#endif //MATH4BG_ICAMERA_H
