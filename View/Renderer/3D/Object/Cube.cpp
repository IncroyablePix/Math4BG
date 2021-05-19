//
// Created by Benjam on 17-04-21.
//

#include "Cube.h"

namespace Math4BG
{

    Cube::Cube(std::shared_ptr<Shader> shader, Transform &transform) : Object3D(shader, cubeIbc, cubeVc, transform)
    {
    }
}