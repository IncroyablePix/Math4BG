//
// Created by Benjam on 11/26/2021.
//

#include "FilesystemUtils.h"

#ifdef WIN32
    #include <windows.h>
#include <regex>
#include <iostream>

#endif

namespace Math4BG
{
    bool CreateFileDirectories(const std::string& path)
    {
#ifdef WIN32
        const char* p = (std::regex_replace(path, std::regex("/"), "\\\\").c_str());
        std::cout << p << std::endl;
        return CreateDirectory(p, nullptr);
#endif
        return false;
    }
}