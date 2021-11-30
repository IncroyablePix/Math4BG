//
// Created by Benjam on 11/30/2021.
//

#include "ProjectPackage.h"
#include <utility>
#include <sstream>

namespace Math4BG
{
    ProjectPackage::ProjectPackage() :
        name("")
    {

    }

    std::shared_ptr<ProjectPackage> ProjectPackage::EmptyProject(const std::string &name, const std::string &language)
    {
        auto pp = std::make_shared<ProjectPackage>();

        pp->name = name;
        pp->language = language;
        pp->fileStructure.files.emplace_back("package.m4bg");
        pp->fileStructure.directories["models"] = std::make_unique<FileStructure>();
        pp->fileStructure.directories["scripts"] = std::make_unique<FileStructure>();
        {
            std::stringstream ss;
            ss << "main." << language;
            pp->fileStructure.directories["scripts"]->files.emplace_back(ss.str());
        }
        pp->fileStructure.directories["shaders"] = std::make_unique<FileStructure>();
        pp->fileStructure.directories["sounds"] = std::make_unique<FileStructure>();
        pp->fileStructure.directories["textures"] = std::make_unique<FileStructure>();

        return pp;
    }
}