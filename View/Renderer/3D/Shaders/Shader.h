//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_SHADER_H
#define MATH4BG_SHADER_H

#include <memory>
#include <string>
#include <sstream>
#include "ShaderProgramSource.h"
#include <unordered_map>
#include <glm/glm.hpp>

namespace Math4BG
{
    class Shader : public std::enable_shared_from_this<Shader>
    {
    public:
        Shader(unsigned int rendererId);

        ~Shader();

        static std::shared_ptr<Shader> CreateShader(ShaderProgramSource source);

        static unsigned int CompileShader(unsigned int type, const std::string &source);

        void Bind() const;
        void Unbind() const;

        unsigned int GetProgramId();

        void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
        void SetUniform1f(const std::string &name, float v);
        void SetUniform1i(const std::string &name, int i);
        void SetUniformMat4(const std::string &name, glm::mat4 m);
        void SetUniformVec4(const std::string &name, glm::vec4 vec4);
        void SetUniformVec3(const std::string &name, const glm::vec3 &v);

    private:
        unsigned int m_rendererId;
        std::unordered_map<std::string, int> m_uniformLocations;

        int GetUniformLocation(const std::string &name);
    };

    //extern Shader Basic;
}

#endif //MATH4BG_SHADER_H
