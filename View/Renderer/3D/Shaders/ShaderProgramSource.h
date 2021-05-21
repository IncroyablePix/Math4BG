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
        VertexShader = 0,
        GeometryShader = 1,
        FragmentShader = 2
    };

    struct ShaderProgramSource
    {
        bool vertex;
        bool geometry;
        bool fragment;

        std::string vertexShaderSource;
        std::string geometryShaderSource;
        std::string fragmentShaderSource;
    };

    ShaderProgramSource ParseShader(std::string filepath);
    ShaderProgramSource ParseShaders(const std::string &vshpath, const std::string &gshpath, const std::string &fshpath);
}

#endif //MATH4BG_SHADERPROGRAMSOURCE_H
