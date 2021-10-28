//
// Created by Benjam on 20-05-21.
//

#ifndef MATH4BG_MODELDATA_H
#define MATH4BG_MODELDATA_H


#include "../View/Renderer/3D/Vertices/IndexBuffer.h"

namespace Math4BG
{
    struct ModelData : public std::enable_shared_from_this<ModelData>
    {
        ModelData() = default;
        ~ModelData() = default;
        ModelData(std::vector<Vertex> &vertices, IndexBufferContainer& ibc) : vertices(vertices), ibc(ibc) { }
        ModelData(Vertex *vertices, unsigned int len, IndexBufferContainer& ibc) : ibc(ibc)
        {
            for(int i = 0; i < len; i ++)
                this->vertices.push_back(vertices[i]);
        }
        std::vector<Vertex> vertices;
        IndexBufferContainer ibc;
    };
}
#endif //MATH4BG_MODELDATA_H
