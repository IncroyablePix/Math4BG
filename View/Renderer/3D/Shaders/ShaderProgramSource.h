//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_SHADERPROGRAMSOURCE_H
#define MATH4BG_SHADERPROGRAMSOURCE_H

#include <string>

namespace Math4BG
{
    enum ShaderType : int32_t
    {
        None = -1,
        Vertex = 0,
        Geometry = 1,
        Fragment = 2
    };

    struct ShaderProgramSource
    {
        std::string vertexShaderSource;
        std::string geometryShaderSource;
        std::string fragmentShaderSource;
    };

    ShaderProgramSource ParseShader(std::string filepath);
    ShaderProgramSource ParseShaders(const std::string &vshpath, const std::string &gshpath, const std::string &fshpath);
}

#endif //MATH4BG_SHADERPROGRAMSOURCE_H
