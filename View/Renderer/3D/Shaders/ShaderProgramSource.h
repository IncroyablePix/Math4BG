//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_SHADERPROGRAMSOURCE_H
#define MATH4BG_SHADERPROGRAMSOURCE_H

#include <string>

namespace Math4BG
{
    enum ShaderType : int
    {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    struct ShaderProgramSource
    {
        std::string vertexShaderSource;
        std::string fragmentShaderSource;
    };

    ShaderProgramSource ParseShader(std::string filepath);
}

#endif //MATH4BG_SHADERPROGRAMSOURCE_H
