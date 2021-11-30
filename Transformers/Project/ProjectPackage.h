//
// Created by Benjam on 11/30/2021.
//

#ifndef MATH4BG_PROJECTPACKAGE_H
#define MATH4BG_PROJECTPACKAGE_H


#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Math4BG
{
    struct FileStructure
    {
        std::vector<std::string> files;
        std::unordered_map<std::string, std::unique_ptr<FileStructure>> directories;
        inline bool Empty() const { return files.empty() && directories.empty(); }
    };

    struct ProjectPackage : public std::enable_shared_from_this<ProjectPackage>
    {
        explicit ProjectPackage();
        std::string name;
        std::string language;
        std::string mainScript;
        FileStructure fileStructure;

        static std::shared_ptr<ProjectPackage> EmptyProject(const std::string &name, const std::string &language);
    };
}

#endif //MATH4BG_PROJECTPACKAGE_H
