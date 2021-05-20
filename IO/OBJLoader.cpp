//
// Created by Benjam on 18-05-21.
//

#include "OBJLoader.h"

#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>

#define FLOAT_REGX          "([+-]?([0-9]+([.][0-9]*)?|[.][0-9]+))"
#define UINT_REGX           "([0-9]+)"

namespace Math4BG
{
    ModelData OBJLoader::LoadModel(const std::string &path)
    {
        ModelData data = { };
        std::ifstream stream(path);
        std::string line;
        std::stringstream ss;
        std::string prefix;

        while (getline(stream, line))
        {
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if(prefix == "v")
                ReadVertexLine(ss, data);
            else if(prefix == "vt")
                ReadUVLine(ss, data);
            else if(prefix == "vn")
                ReadNormalsLine(ss, data);
            else if(prefix == "f")
                ReadIndicesLine(ss, data);
        }

        return data;
    }

    void OBJLoader::ReadVertexLine(std::stringstream &line, ModelData &data)
    {
        glm::vec3 vertex;
        line >> vertex.x >> vertex.y >> vertex.z;
        data.vc.Push(vertex);
    }

    void OBJLoader::ReadUVLine(std::stringstream &line, ModelData &data)
    {
        glm::vec2 uv;
        line >> uv.x >> uv.y;
        data.outUVs.push_back(uv);
    }

    void OBJLoader::ReadNormalsLine(std::stringstream &line, ModelData &data)
    {
        glm::vec3 vertex;
        line >> vertex.x >> vertex.y >> vertex.z;
        data.outNormals.push_back(vertex);
    }

    void OBJLoader::ReadIndicesLine(std::stringstream &line, ModelData &data)
    {
        int i = 0;
        unsigned int tempUInt;

        while(line >> tempUInt)
        {
            switch(i)
            {
                case 0:
                    data.ibc.Push(tempUInt - 1);
                    break;
                case 1:
                    data.outUVIndices.push_back(tempUInt - 1);
                    break;
                case 2:
                    data.outNormalIndices.push_back(tempUInt - 1);
                    break;
            }

            if(line.peek() == '/' || line.peek() == ' ')
            {
                i ++;
                line.ignore(1, '/');
            }

            if(i > 2)
                i = 0;
        }
    }
}