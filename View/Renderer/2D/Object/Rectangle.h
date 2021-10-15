//
// Created by Benjam on 16-04-21.
//

#ifndef MATH4BG_RECTANGLE_H
#define MATH4BG_RECTANGLE_H


#include "Point.h"
#include "Object2D.h"

namespace Math4BG
{
    class Rectangle : public Object2D
    {
    public:
        Rectangle();
        Rectangle(std::shared_ptr<Shader> shader, const glm::vec3 &position, const glm::vec2 &dimens, uint32_t color);
        ~Rectangle();

        Point m_start;
        float m_height;
        float m_width;

    private:

        inline static Vertex vertices [] =
                {
                        {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
                        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}
                };

        inline static unsigned int indices[] =
                {
                        0, 1, 2,
                        0, 2, 3
                };

        inline static IndexBufferContainer ibc = {indices, 6 };

        inline static ModelData model {vertices, 4, ibc };
    };
}

#endif //MATH4BG_RECTANGLE_H
