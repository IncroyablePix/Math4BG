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

//#define UINT_MAX            (0xFFFFFFFF)

namespace Math4BG
{
    ModelData OBJLoader::LoadModel(const std::string &path)
    {
        ModelData data = { };

        std::vector<unsigned int> outVertexIndices;
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
                ReadIndicesLine(ss, outVertexIndices, outUVIndices, outNormalIndices);
        }

        for(int i = 0, j = outVertexIndices.size(); i < j; i ++)
        {
            Vertex vertex;

            unsigned int vertexIndex = outVertexIndices[i];
            unsigned int uvIndex = outUVIndices[i];
            unsigned int normalIndex = outNormalIndices[i];

            vertex.position = vc[vertexIndex];
            vertex.uvs = (uvIndex == UINT_MAX ? glm::vec2(0.0, 0.0) : outUVs[uvIndex]);
            vertex.normal = (normalIndex == UINT_MAX ? glm::vec3(1.0f, 1.0f, 1.0f) : outNormals[normalIndex]);
            vertex.col = glm::vec3(1.0f, 1.0f, 1.0f);

            data.vertices.push_back(vertex);
        }

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

    void OBJLoader::ReadIndicesLine(std::stringstream &line, std::vector<unsigned int> &outVertexIndices, std::vector<unsigned int> &outUVIndices, std::vector<unsigned int> &outNormalIndices)
    {
        int i = 0, j = 0;
        std::vector<unsigned int> temp; // hoping that n-gons are an exception!!
        unsigned int tempUInt;

        while(line >> tempUInt)
        {
            tempUInt --; // stupid obj file format starting at index 1
            temp.push_back(tempUInt);

            while(line.peek() == '/' || line.peek() == ' ')
                line.ignore(1, '/');
        }

        //--- Triangulization (proper word?)
        j = temp.size();
        switch(j)
        {
            case 3:
                for(i = 0; i < 3; i ++)
                {
                    outVertexIndices.push_back(temp[i]);
                    outUVIndices.push_back(UINT_MAX);
                    outNormalIndices.push_back(UINT_MAX);
                }
                break;
            case 4:
                outVertexIndices.push_back(temp[0]); // Triangle 1
                outVertexIndices.push_back(temp[1]);
                outVertexIndices.push_back(temp[2]);

                outVertexIndices.push_back(temp[2]);
                outVertexIndices.push_back(temp[3]);
                outVertexIndices.push_back(temp[0]);

                for(i = 0; i < 6; i ++)
                {
                    outUVIndices.push_back(UINT_MAX);
                    outNormalIndices.push_back(UINT_MAX);
                }
                break;
            case 5:
                break;
            case 9: // Best way
                for(i = 0; i < 3; i ++)
                {
                    outVertexIndices.push_back(temp[3 * i]);
                    outUVIndices.push_back(temp[3 * i + 1]);
                    outNormalIndices.push_back(temp[3 * i + 2]);
                }
                break;
            case 12:
                // Triangle 1
                outVertexIndices.push_back(temp[0]); // v1
                outUVIndices.push_back(temp[1]);
                outNormalIndices.push_back(temp[2]);

                outVertexIndices.push_back(temp[3]); // v2
                outUVIndices.push_back(temp[4]);
                outNormalIndices.push_back(temp[5]);

                outVertexIndices.push_back(temp[6]); // v3
                outUVIndices.push_back(temp[7]);
                outNormalIndices.push_back(temp[8]);

                // Triangle 2
                outVertexIndices.push_back(temp[6]); // v3
                outUVIndices.push_back(temp[7]);
                outNormalIndices.push_back(temp[8]);

                outVertexIndices.push_back(temp[9]); // v4
                outUVIndices.push_back(temp[10]);
                outNormalIndices.push_back(temp[11]);

                outVertexIndices.push_back(temp[0]); // v1
                outUVIndices.push_back(temp[1]);
                outNormalIndices.push_back(temp[2]);

                break;
            case 15:
                break;
        }
    }
}