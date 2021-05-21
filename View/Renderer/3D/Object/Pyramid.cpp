//
// Created by Benjam on 21-05-21.
//

#include "Pyramid.h"


namespace Math4BG
{

    Pyramid::Pyramid(std::shared_ptr<Shader> shader, Transform &transform) : Object3D(shader, &pyramidModel, transform)
    {
    }
}