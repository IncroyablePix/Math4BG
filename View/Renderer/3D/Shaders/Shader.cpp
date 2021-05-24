//
// Created by Benjam on 13-04-21.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.h"
#include "../GL/GLMacros.h"


namespace Math4BG
{
    Shader::Shader(unsigned int rendererId) :
            m_rendererId(rendererId)
    {

    }

    Shader::~Shader()
    {
        if(m_rendererId != 0)
        {
            GLCall(glDeleteProgram(m_rendererId));
        }
    }

    std::shared_ptr<Shader> Shader::CreateShader(ShaderProgramSource source)
    {
        bool geometry;
        unsigned int shaderProgram = glCreateProgram();
        unsigned int vertexShader;
        unsigned int geometryShader;
        unsigned int fragmentShader;
        vertexShader = CompileShader(GL_VERTEX_SHADER, source.vertexShaderSource);

        if(source.geometry)
            geometryShader = CompileShader(GL_GEOMETRY_SHADER, source.geometryShaderSource);

        fragmentShader = CompileShader(GL_FRAGMENT_SHADER, source.fragmentShaderSource);

        GLCall(glAttachShader(shaderProgram, vertexShader));
        if(source.geometry)
        {
            GLCall(glAttachShader(shaderProgram, geometryShader));
        }

        GLCall(glAttachShader(shaderProgram, fragmentShader));
        GLCall(glLinkProgram(shaderProgram));
        GLCall(glValidateProgram(shaderProgram));

        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));

        return std::make_shared<Shader>(shaderProgram);
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
    {
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();

        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));


        if (result == GL_FALSE)
        {
            int length;
            std::stringstream ss;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char *message = (char *) alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));

            ss << "Could not compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl
               << message << std::endl;

            GLCall(glDeleteShader(id));
            throw std::runtime_error(ss.str());
        }

        return id;
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(m_rendererId))
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3))
    }

    int Shader::GetUniformLocation(const std::string &name)
    {
        if (m_uniformLocations.find(name) != m_uniformLocations.end())
            return m_uniformLocations[name];

        GLCall(int location = glGetUniformLocation(m_rendererId, name.c_str()));

        if (location == -1)
            std::cout << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;

        m_uniformLocations[name] = location;

        return location;
    }

    void Shader::SetUniform1f(const std::string &name, float v)
    {
        GLCall(glUniform1f(GetUniformLocation(name), v))
    }

    void Shader::SetUniformVec3(const std::string &name, const glm::vec3 &v)
    {
        GLCall(glUniform3fv(GetUniformLocation(name), 1, (GLfloat *) &v));
    }

    void Shader::SetUniformMat4(const std::string &name, glm::mat4 m)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m[0][0]))
    }

    void Shader::SetUniformVec4(const std::string &name, glm::vec4 vec4)
    {
        GLCall(glUniform4fv(GetUniformLocation(name), 1, (GLfloat *) &vec4));
    }

    void Shader::SetUniform1i(const std::string &name, int i)
    {
        GLCall(glUniform1i(GetUniformLocation(name), i));
    }

    unsigned int Shader::GetProgramId()
    {
        return m_rendererId;
    }
}
