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

        std::vector<unsigned int> outUVIndices;
        std::vector<unsigned int> outNormalIndices;

        std::vector<glm::vec2> outUVs;
        std::vector<glm::vec3> outNormals;

        std::vector<glm::fvec3> vc;

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
                ReadVertexLine(ss, vc);
            else if(prefix == "vt")
                ReadUVLine(ss, outUVs);
            else if(prefix == "vn")
                ReadNormalsLine(ss, outNormals);
            else if(prefix == "f")
                ReadIndicesLine(ss, data, outUVIndices, outNormalIndices);
        }

        //std::cout << "Vertices count " << data.vc.size() << std::endl;

        data.vertices.resize(vc.size(), Vertex());

        for(int i = 0; i < data.vertices.size(); i ++)
        {
            data.vertices[i].position = vc[i];
            data.vertices[i].texcoord = outUVs[i];
            data.vertices[i].normal = outNormals[i];
            data.vertices[i].col = glm::vec3(1.0f, 1.0f, 1.0f);
        }
        /*data.vertices.resize(data.ibc.Entries(), Vertex());

        for(int i = 0; i < data.vertices.size(); i ++)
        {
            data.vertices[i].position = vc[data.ibc.vertices[i]];
            data.vertices[i].texcoord = outUVs[outUVIndices[i]];
            data.vertices[i].normal = outNormals[outNormalIndices[i]];
            data.vertices[i].col = glm::vec3(1.0f, 1.0f, 1.0f);
        }*/

        //data.ibc.vertices.clear();


        /*for(int i = 0; i < vertices.size(); i ++)
        {
            std::cout << v
        }*/

        return data;
    }

    void OBJLoader::ReadVertexLine(std::stringstream &line, std::vector<glm::fvec3> &vc)
    {
        glm::vec3 vertex;
        line >> vertex.x >> vertex.y >> vertex.z;
        vc.push_back(vertex);
    }

    void OBJLoader::ReadUVLine(std::stringstream &line, std::vector<glm::vec2> &outUVs)
    {
        glm::vec2 uv;
        line >> uv.x >> uv.y;
        outUVs.push_back(uv);
    }

    void OBJLoader::ReadNormalsLine(std::stringstream &line, std::vector<glm::vec3> &outNormals)
    {
        glm::vec3 vertex;
        line >> vertex.x >> vertex.y >> vertex.z;
        outNormals.push_back(vertex);
    }

    void OBJLoader::ReadIndicesLine(std::stringstream &line, ModelData &data, std::vector<unsigned int> &outUVIndices, std::vector<unsigned int> &outNormalIndices)
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
                    outUVIndices.push_back(tempUInt - 1);
                    break;
                case 2:
                    outNormalIndices.push_back(tempUInt - 1);
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