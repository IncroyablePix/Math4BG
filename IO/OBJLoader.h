//
// Created by Benjam on 18-05-21.
//

#ifndef MATH4BG_OBJLOADER_H
#define MATH4BG_OBJLOADER_H

#include <regex>
#include "IModelLoader.h"

namespace Math4BG
{
    class OBJLoader : public IModelLoader
    {
    public:
        std::shared_ptr<ModelData> LoadModel(const std::string &path) override;

    private:
        void ReadVertexLine(std::stringstream &line, std::vector<glm::fvec3> &vc);
        void ReadUVLine(std::stringstream &line, std::vector<glm::vec2> &outUVs);
        void ReadNormalsLine(std::stringstream &line, std::vector<glm::vec3> &outNormals);
        void ReadIndicesLine(std::stringstream &line, std::vector<unsigned int> &outVertexIndices, std::vector<unsigned int> &outUVIndices, std::vector<unsigned int> &outNormalIndices);
    };
}



#endif //MATH4BG_OBJLOADER_H
