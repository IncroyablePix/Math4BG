//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_LINE_H
#define MATH4BG_LINE_H

#include "Object2D.h"
#include "Point.h"
#include "../../../../IO/ModelData.h"

namespace Math4BG
{
    class Line : public Object2D
    {
    public:
        Line();
        Line(std::shared_ptr<Shader> shader, const glm::vec3 &start, const glm::vec3 &end, uint32_t color);
        ~Line();

        glm::vec3 m_start;
        glm::vec3 m_end;

    private:
        inline static Vertex vertices [] =
                {
                        {{-1.0f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.66f}, {0.0f, -1.0f, 0.0f}},
                        {{-1.0f, 0.1f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 0.66f}, {0.0f, -1.0f, 0.0f}},
                        {{1.0f, 0.1f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 0.34f}, {0.0f, -1.0f, 0.0f}},
                        {{1.0f, -0.1f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.75f, 0.34f}, {0.0f, 1.0f, 0.0f}}
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

#endif //MATH4BG_LINE_H
