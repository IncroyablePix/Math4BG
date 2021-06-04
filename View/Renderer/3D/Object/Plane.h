//
// Created by Benjam on 25-05-21.
//

#ifndef MATH4BG_PLANE_H
#define MATH4BG_PLANE_H

#include "Object3D.h"

namespace Math4BG
{
    class Plane : public Object3D
    {

    public:
        Plane(std::shared_ptr<Shader> shader, Transform &transform);

    private:
        inline static Vertex vertices [] =
                {
                        {{0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},// bottom 1
                        {{-0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{-0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},

                        {{-0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},// top 1
                        {{-0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
                        {{0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

                        {{0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // bottom 2
                        {{0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
                        {{-0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},

                        {{0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // top 2
                        {{-0.5, 0.0, -0.5}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                        {{0.5, 0.0, 0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}
                };

        inline static unsigned int indices[] =
                {
                };

        inline static IndexBufferContainer ibc = {{}, 0 };

        inline static ModelData model {vertices, 36, ibc };
    };
}

#endif //MATH4BG_PLANE_H
