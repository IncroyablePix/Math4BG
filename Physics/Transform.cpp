//
// Created by Benjam on 19-05-21.
//

#include "Transform.h"

Math4BG::Transform Math4BG::Transform::operator+(const Math4BG::Transform &t1)
{
    Transform res;

    res.Position = Position + t1.Position;
    res.Origin = Origin + t1.Origin;
    res.Rotation = Rotation + t1.Rotation;
    res.Scale = Scale * t1.Scale;

    return res;
}
