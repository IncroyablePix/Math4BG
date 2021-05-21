//
// Created by Benjam on 18-05-21.
//

#ifndef MATH4BG_OBJLOADER_H
#define MATH4BG_OBJLOADER_H

#include <regex>
#include "IModelLoader.h"

namespace Math4BG
{
    class OBJLoader : IModelLoader
    {
    public:
        ModelData LoadModel(const std::string &path) override;

    private:
        void ReadVertexLine(std::stringstream &line, std::vector<glm::fvec3> &vc);
        void ReadUVLine(std::stringstream &line, std::vector<glm::vec2> &outUVs);
        void ReadNormalsLine(std::stringstream &line, std::vector<glm::vec3> &outNormals);
        void ReadIndicesLine(std::stringstream &line, std::vector<unsigned int> &outVertexIndices, std::vector<unsigned int> &outUVIndices, std::vector<unsigned int> &outNormalIndices);

        /*template<typename T>
        inline void ReadVectorLine(const std::string &line, std::vector<T> vector, size_t vectorSize)
        {
            int i = 0;
            glm::vec3 vertex;
            const std::string floatRegex = "([+-]?([0-9]+([.][0-9]*)?|[.][0-9]+))";

            std::regex rx(floatRegex);
            std::smatch matches;
            std::string toSearch = line;

            while(std::regex_search(toSearch, matches, rx) && i < vectorSize)
            {
                switch(i)
                {
                    case 0:
                        vertex.x = std::stof(matches[1]);
                        break;
                    case 1:
                        vertex.y = std::stof(matches[1]);
                        break;
                    case 2:
                        vertex.z = std::stof(matches[1]);
                        break;
                }
                toSearch = matches.suffix().str();
                i ++;
            }
            vector.push_back(vertex);
        }*/
    };
}



#endif //MATH4BG_OBJLOADER_H
