//
// Created by Benjam on 10/29/2021.
//

#ifndef MATH4BG_CODEEXCEPTION_H
#define MATH4BG_CODEEXCEPTION_H

#include <stdexcept>

namespace Math4BG
{
    class CodeException : public std::runtime_error
    {
    public:
        explicit CodeException(const std::string& what) : std::runtime_error(what.c_str()) { }
    };
}

#endif //MATH4BG_CODEEXCEPTION_H
