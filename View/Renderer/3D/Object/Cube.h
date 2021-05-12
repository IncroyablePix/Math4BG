//
// Created by Benjam on 17-04-21.
//

#ifndef MATH4BG_CUBE_H
#define MATH4BG_CUBE_H

#include "Object3D.h"

namespace Math4BG
{
    class Cube : public Object3D
    {
    public:
        Cube(std::shared_ptr<Shader> shader);

    private:
        inline const static VerticesContainer cubeVc =
                {
                (new float[24]
                        {
                                -0.5f, -0.5f, 0.03f,
                                0.5f, -0.5f, 0.03f,

                                0.5f, 0.5f, 0.03f,
                                -0.5f, 0.5f, 0.03f,

                                -0.5f, -0.5f, -1.0f,
                                0.5f, -0.5f, -1.0f,

                                0.5f, 0.5f, -1.0f,
                                -0.5f, 0.5f, -1.0f
                        }), sizeof(float) * 8 * 3
                };

        inline const static IndexBufferContainer cubeIbc =
                { (new unsigned int[36]
                    {
                            0, 1, 2, // Face en face
                            2, 3, 0,

                            0, 1, 4, // Face du bas
                            1, 4, 5,

                            3, 4, 7, // Face gauche
                            0, 3, 4,

                            4, 5, 9, // Face arrière
                            6, 7, 4,

                            2, 3, 6, // Face du haut
                            3, 6, 7,

                            1, 2, 5, // Face droite
                            2, 5, 6
                    }),
                  36
                };
    };
}

#endif //MATH4BG_CUBE_H
