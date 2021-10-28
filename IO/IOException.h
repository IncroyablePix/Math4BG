//
// Created by Benjam on 10/26/2021.
//

#ifndef MATH4BG_IOEXCEPTION_H
#define MATH4BG_IOEXCEPTION_H

#include <string>
#include <stdexcept>

namespace Math4BG
{
    class IOException : public std::runtime_error
    {
    public:
        IOException() : std::runtime_error("") { }
        explicit IOException(const std::string& what) : std::runtime_error(what.c_str()) { }
    };
}

#endif //MATH4BG_IOEXCEPTION_H
