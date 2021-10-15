//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_CIRCLE_H
#define MATH4BG_CIRCLE_H

#include "Object2D.h"
#include "Point.h"

namespace Math4BG
{
    class Circle : public Object2D
    {
    public:
        Circle();
        Circle(std::shared_ptr<Shader> shader, glm::vec3 center, double radius, uint32_t color);
        ~Circle();
        //void Draw(SDL_Surface* surface, const Point &size) override;

        glm::vec3 m_center;
        double m_radius;

    private:

        inline static Vertex vertices [] =
                {
                        {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
                        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{0.5f, -0.5f, 0.0f}, {1, 1, 1}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}
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

#endif //MATH4BG_CIRCLE_H
