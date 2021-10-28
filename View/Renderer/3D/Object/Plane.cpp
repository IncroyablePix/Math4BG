//
// Created by Benjam on 25-05-21.
//

#include "Plane.h"

namespace Math4BG
{
    Plane::Plane(std::shared_ptr<Shader> shader, Math4BG::Transform &transform) : Object3D(shader, model, transform)
    {

    }
}
