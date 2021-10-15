//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_IDRAWABLE_H
#define MATH4BG_IDRAWABLE_H

#include <memory>
#include "../3D/Camera/ICamera.h"

namespace Math4BG
{
    class IDrawable : std::enable_shared_from_this<IDrawable>
    {
    public:
        virtual ~IDrawable() = default;
        virtual void Bind(const ICamera& camera) const = 0;
        virtual void Unbind() const = 0;

        void SetColor(const glm::vec4 &color);

    protected:
        glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    };
}

#endif //MATH4BG_IDRAWABLE_H
