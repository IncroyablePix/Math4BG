//
// Created by Benjam on 12-05-21.
//

#ifndef MATH4BG_FILESPLIT_H
#define MATH4BG_FILESPLIT_H

#include <string>

namespace Math4BG
{
    struct FileSplit
    {
        FileSplit(const std::string &filePath);

        std::string fileName;
        std::string filePath;
        std::string fileExtension;
        std::string fileWithoutExtension;
    };
}

#endif //MATH4BG_FILESPLIT_H
