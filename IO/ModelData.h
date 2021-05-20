//
// Created by Benjam on 20-05-21.
//

#ifndef MATH4BG_MODELDATA_H
#define MATH4BG_MODELDATA_H


#include "../View/Renderer/3D/Vertices/IndexBuffer.h"

namespace Math4BG
{
    struct ModelData
    {
        std::vector<unsigned int> outUVIndices;
        std::vector<unsigned int> outNormalIndices;

        std::vector<glm::vec2> outUVs;
        std::vector<glm::vec3> outNormals;

        VerticesContainer vc;
        IndexBufferContainer ibc;

        friend std::ostream& operator<<(std::ostream& out, ModelData& data)
        {
            out << "UVs :" << std::endl;
            for(auto v : data.outUVs)
                out << v.x << ", " << v.y << std::endl;
            out << "Normals :" << std::endl;
            for(auto v : data.outNormals)
                out << v.x << ", " << v.y << ", " << v.z << std::endl;

            out << "UV indices :" << std::endl;
            for(auto v : data.outUVIndices)
                out << v << std::endl;
            out << "Normals indices :" << std::endl;
            for(auto v : data.outNormalIndices)
                out << v << std::endl;

            return out;
        }
    };
}
#endif //MATH4BG_MODELDATA_H
