//
// Created by Benjam on 13-04-21.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "Shader.h"
#include "../GL/GLMacros.h"


namespace Math4BG
{
    /*Shader Basic = *Shader::CreateShader(
{
        "#version 330 core\n"
        "layout(location = 0) in vec3 inPosition;\n"
        "layout(location = 1) in vec2 inCoord;\n"
        "layout(location = 2) in vec3 inNormal;\n"
        "\n"
        "out vec2 texCoord;\n"
        "smooth out vec3 vNormal;\n"
        "\n"
        "uniform mat4 projectionMatrix;\n"
        "uniform mat4 normalMatrix;\n"
        "uniform mat4 modelViewMatrix;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projectionMatrix * modelViewMatrix * vec4(inPosition, 1.0);\n"
        "    texCoord = inCoord;\n"
        "    vec4 vRes = normalMatrix * vec4(inNormal, 0.0);\n"
        "    vNormal = vRes.xyz;\n"
        "}\n"
        "\n",

        "",

        "#shader fragment\n"
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "uniform vec4 vColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}"
    });*/

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

    void Shader::SetUniformVec3(const std::string &name, glm::vec3 vec3)
    {
        GLCall(glUniform3fv(GetUniformLocation(name), 1, (GLfloat *) &vec3));
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
