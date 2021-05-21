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
        //inline static VerticesContainer cubeVc = { cubeVertices, 24 };

        inline static unsigned int verticesIndexes[] =
        {
                0, 1, 2,
                0, 2, 3,

                7, 6, 1,
                4, 5, 6,

                4, 5, 6,
                4, 6, 7,

                3, 2, 5,
                3, 5, 4
                /*0, 1, 2, // Face en face
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
                2, 5, 6*/
        };
        inline static IndexBufferContainer cubeIbc = { verticesIndexes, 24 };

        inline static ModelData cubeModel { cubeVertices, 8, cubeIbc };
        /*
         *
        std::vector<Vertex> vertices;
        IndexBufferContainer ibc;
         */
    };
}

#endif //MATH4BG_CUBE_H
