//
// Created by Benjam on 13-04-21.
//

#include "ShaderProgramSource.h"

#include <sstream>
#include <fstream>


namespace Math4BG
{
    ShaderProgramSource ParseShader(std::string filepath)
    {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss[2];

        ShaderType type = ShaderType::None;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::Vertex;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::Fragment;
            } else
            {
                ss[type] << line << std::endl;
            }
        }

        return {ss[0].str(), ss[1].str()};
    }
}