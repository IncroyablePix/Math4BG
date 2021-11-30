//
// Created by Benjam on 11/30/2021.
//

#include <fstream>
#include "ProjectSaverLoader.h"
#include "../../IO/Json/json.hpp"
#include "../../IO/IOException.h"

namespace Math4BG
{
    //--- Loader

    static void ReadFilesArray(const nlohmann::json &json, FileStructure &fileStructure)
    {
        for(const auto & i : json)
        {
            fileStructure.files.emplace_back(i);
        }
    }

    static void ReadDirectoriesArray(const nlohmann::json &json, FileStructure &fileStructure)
    {
        for(const auto & i : json.items())
        {
            const auto& name = i.key();
            const auto& structure = fileStructure.directories[name] = std::make_unique<FileStructure>();

            ReadFilesArray(i.value()["files"], *structure);
            ReadDirectoriesArray(i.value()["directories"], *structure);
        }
    }

    std::shared_ptr<ProjectPackage> LoadFromFile(const std::string &path)
    {
        nlohmann::json j;
        std::ifstream file(path);
        file >> j;

        auto projectPackage = std::make_shared<ProjectPackage>();
        projectPackage->name = j["projectName"].get<std::string>();
        projectPackage->language = j["projectLanguage"].get<std::string>();
        projectPackage->mainScript = j["projectMain"].get<std::string>();
        ReadFilesArray(j["files"], projectPackage->fileStructure);
        ReadDirectoriesArray(j["directories"], projectPackage->fileStructure);

        return projectPackage;
    }

    //--- Saver

    static nlohmann::json CreateFilesArray(const FileStructure &fileStructure)
    {
        nlohmann::json array = nlohmann::json::array();
        for(const auto& f : fileStructure.files)
        {
            array.push_back(f);
        }

        return array;
    }

    static nlohmann::json CreateDirectoriesArray(const FileStructure &fileStructure)
    {
        nlohmann::json array = nlohmann::json::object();

        for(const auto& [name, dir] : fileStructure.directories)
        {
            nlohmann::json object;
            object["files"] = CreateFilesArray(*dir);
            object["directories"] = CreateDirectoriesArray(*dir);
            array[name] = object;
        }

        return array;
    }

    bool SaveToFile(const std::string &path, const std::shared_ptr<ProjectPackage>& projectPackage)
    {
        std::ofstream file(path);

        if(!file.good())
        {
            throw IOException("Could not open file");
        }

        nlohmann::json j = {
                {"projectName", projectPackage->name},
                {"projectLanguage", projectPackage->language},
                {"projectMain", projectPackage->mainScript},
                {"files", CreateFilesArray(projectPackage->fileStructure)},
                {"directories", CreateDirectoriesArray(projectPackage->fileStructure)}
        };

        file << j;
        return true;
    }
}