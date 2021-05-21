//
// Created by Benjam on 17-04-21.
//

#ifndef MATH4BG_CUBE_H
#define MATH4BG_CUBE_H

#include "Object3D.h"
#include "../../../../Physics/Transform.h"

namespace Math4BG
{
    class Cube : public Object3D
    {
    public:
        Cube(std::shared_ptr<Shader> shader, Transform &transform);

    private:
        inline static Vertex cubeVertices[] = {
                //Position					//Color				//Texcoords		//Normals
                {{-0.5f, 0.5f, 0.5f},       {1.f, 0.f, 0.f},	{0.f, 1.f},		{0.f, 0.f, 1.f}},
                {{-0.5f, -0.5f, 0.5f},	    {0.f, 1.f, 0.f},	{0.f, 0.f},		{0.f, 0.f, 1.f}},
                {{0.5f, -0.5f, 0.5f},		{0.f, 0.f, 1.f},	{1.f, 0.f},		{0.f, 0.f, 1.f}},
                {{0.5f, 0.5f, 0.5f},		{1.f, 1.f, 0.f},	{1.f, 1.f},		{0.f, 0.f, 1.f}},

                {{0.5f, 0.5f, -0.5f},		{1.f, 0.f, 0.f},	{0.f, 1.f},		{0.f, 0.f, -1.f}},
                {{0.5f, -0.5f, -0.5f},		{0.f, 1.f, 0.f},	{0.f, 0.f},		{0.f, 0.f, -1.f}},
                {{-0.5f, -0.5f, -0.5f}, 	{0.f, 0.f, 1.f},	{1.f, 0.f},		{0.f, 0.f, -1.f}},
                {{-0.5f, 0.5f, -0.5f},		{1.f, 1.f, 0.f},	{1.f, 1.f},		{0.f, 0.f, -1.f}}
        };

        inline static unsigned int verticesIndexes[] =
        {
                0, 1, 2,
                0, 2, 3,

                7, 6, 1,
                0, 7, 1,

                4, 5, 6,
                4, 6, 7,

                3, 2, 5,
                4, 3, 5,

                0, 3, 4,
                0, 4, 7,

                5, 2, 1,
                6, 5, 1
        };
        inline static IndexBufferContainer cubeIbc = { verticesIndexes, 36 };

        inline static ModelData cubeModel { cubeVertices, 8, cubeIbc };
    };
}

#endif //MATH4BG_CUBE_H
