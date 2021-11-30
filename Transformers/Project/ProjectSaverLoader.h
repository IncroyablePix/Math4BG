//
// Created by Benjam on 11/30/2021.
//

#ifndef MATH4BG_PROJECTSAVERLOADER_H
#define MATH4BG_PROJECTSAVERLOADER_H

#include <memory>
#include "ProjectPackage.h"

namespace Math4BG
{
    bool SaveToFile(const std::string &path, const std::shared_ptr<ProjectPackage>& projectPackage);
    std::shared_ptr<ProjectPackage> LoadFromFile(const std::string &path);
}

#endif //MATH4BG_PROJECTSAVERLOADER_H
