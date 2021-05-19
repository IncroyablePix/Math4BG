//
// Created by Benjam on 18-05-21.
//

#ifndef MATH4BG_IMODELLOADER_H
#define MATH4BG_IMODELLOADER_H

#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace Math4BG
{
    enum DataType : int32_t
    {
        NoData = -1,
        Vertex = 0,
        UV = 1,
        Normals = 2
    };

    struct ModelData
    {
        std::vector<glm::vec3> outVertices;
        std::vector<glm::vec2> outUVs;
        std::vector<glm::vec3> outNormals;
    };

    class IModelLoader
    {
    public:
        virtual ModelData LoadModel(const std::string &path) = 0;
    };
}

#endif //MATH4BG_IMODELLOADER_H
