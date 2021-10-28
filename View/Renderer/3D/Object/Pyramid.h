//
// Created by Benjam on 21-05-21.
//

#ifndef MATH4BG_PYRAMID_H
#define MATH4BG_PYRAMID_H

#include "Object3D.h"

namespace Math4BG
{
    class Pyramid : public Object3D
    {
    public:
        Pyramid(std::shared_ptr<Shader> shader, Transform &transform);

    private:
        inline static Vertex vertices[] =
        {
                //Position								//Color							//UV					//Normals
                //Triangle front
                {{0.0f, 0.5f, 0.0f},	    {1.0f, 0.0f, 0.0f},    {0.5f, 1.0f},	{0.0f, 0.0f, 1.0f}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 1.0f, 0.0f},	    {0.0f, 0.0f},		{0.0f, 0.0f, 1.0f}},
                {{0.5f, -0.5f, 0.5f},	    {0.0f, 0.0f, 1.0f},		{1.0f, 0.0f},		{0.0f, 0.0f, 1.0f}},

                //Triangle left
                {{0.0f, 0.5f, 0.0f},	    {1.0f, 1.0f, 0.0f},		{0.5f, 1.0f},	{-1.0f, 0.0f, 0.0f}},
                {{-0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},		{0.0f, 0.0f},		{-1.0f, 0.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.5f},{0.0f, 0.0f, 1.0f},		{1.0f, 0.0f},		{-1.0f, 0.0f, 0.0f}},

                //Triangle back
                {{0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},		{0.0f, 0.0f},		{0.0f, 0.0f, -1.0f}},
                {{0.0f, 0.5f, 0.0f},	{1.0f, 1.0f, 0.0f},		{0.5f, 1.0f},	{0.0f, 0.0f, -1.0f}},
                {{-0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},		{1.0f, 0.0f},		{0.0f, 0.0f, -1.0f}},

                //Triangles right
                {{0.0f, 0.5f, 0.0f},	{1.0f, 1.0f, 0.0f},		{0.5f, 1.0f},	{1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f, 0.5f},	{0.0f, 0.0f, 1.0f},		{0.0f, 0.0f},		{1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f, -0.5f},{0.0f, 0.0f, 1.0f},		{1.0f, 0.0f},		{1.0f, 0.0f, 0.0f}}
        };

        inline static unsigned int verticesIndexes[] =
        {
                0, 1, 2, // back
                5, 3, 4, // left
                7, 6, 8, // front
                10, 9, 11, // right

                5, 4, 6,
                2, 5, 6 // bottom
        };
        inline static IndexBufferContainer pyramidIbc = {verticesIndexes, 18 };

        inline static std::shared_ptr<ModelData> pyramidModel = std::make_shared<ModelData>(vertices, 8, pyramidIbc);
    };
}

#endif //MATH4BG_PYRAMID_H
