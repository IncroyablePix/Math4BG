//
// Created by Benjam on 13-04-21.
//

#include "ShaderProgramSource.h"
#include "ShaderException.h"

#include <sstream>
#include <fstream>


namespace Math4BG
{
    ShaderProgramSource ParseShader(std::string filepath)
    {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss[3];
        bool shaderFound[3] = { false, false, false };

        ShaderType type = ShaderType::None;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VertexShader;
                else if(line.find("geometry") != std::string::npos)
                    type = ShaderType::GeometryShader;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FragmentShader;

                shaderFound[type] = true;
            }
            else
            {
                ss[type] << line << std::endl;
            }
        }

        if(!shaderFound[0] || !shaderFound[2])
        {
            std::stringstream es;
            es << "Invalid shader file: " << "\"" << filepath << "\"";
            throw ShaderException(es.str());
        }

        const std::string vertexShader = ss[0].str();
        const std::string geometryShader = ss[1].str();
        const std::string fragmentShader = ss[2].str();

        return {shaderFound[0], shaderFound[1], shaderFound[2],
                vertexShader, geometryShader, fragmentShader };
    }

    //---

    void ReadShaderSource(const std::string &filepath, ShaderProgramSource& source, ShaderType type)
    {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss;

        while(getline(stream, line))
        {
            ss << line << std::endl;
        }

        switch(type)
        {
            case VertexShader:
                source.vertexShaderSource = ss.str();
                break;
            case GeometryShader:
                source.geometryShaderSource = ss.str();
                break;
            case FragmentShader:
                source.fragmentShaderSource = ss.str();
                break;
        }
    }

    ShaderProgramSource ParseShaders(const std::string &vshpath, const std::string &gshpath, const std::string &fshpath)
    {
        ShaderProgramSource source;

        ReadShaderSource(vshpath, source, VertexShader);
        ReadShaderSource(gshpath, source, GeometryShader);
        ReadShaderSource(fshpath, source, FragmentShader);

        return source;
    }
}