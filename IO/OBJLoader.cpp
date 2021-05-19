//
// Created by Benjam on 18-05-21.
//

#include "OBJLoader.h"

#include <sstream>
#include <fstream>

namespace Math4BG
{
    ModelData OBJLoader::LoadModel(const std::string &path)
    {
        std::ifstream stream(path);
        std::string line;
        std::stringstream ss[3];

        DataType type = DataType::NoData;

        while (getline(stream, line))
        {
            if(line[0] == 'v')
            {

            }
            //if (line.find("#shader") != std::string::npos)
        }

        return {};
    }
}