//
// Created by Benjam on 10/26/2021.
//

#ifndef MATH4BG_SHADEREXCEPTION_H
#define MATH4BG_SHADEREXCEPTION_H

#include <stdexcept>

namespace Math4BG
{
    class ShaderException : public std::runtime_error
    {
    public:
        explicit ShaderException(const std::string& what) : std::runtime_error(what.c_str()) { }
    };
}

#endif //MATH4BG_SHADEREXCEPTION_H
