//
// Created by Benjam on 11/30/2021.
//

#include <fstream>
#include <unistd.h>
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
            FileElement fileElement = { i, "" };
            fileStructure.files.emplace_back(fileElement);
        }
    }

    static void ReadDirectoriesArray(const nlohmann::json &json, FileStructure &fileStructure)
    {
        for(const auto & i : json.items())
        {
            const auto& name = i.key();
            const auto& structure = fileStructure.directories[name] = std::make_unique<FileStructure>();

            auto ivalue = i.value();

            if(ivalue.contains("files") && ivalue["files"].is_array() &&
                ivalue.contains("directories") && ivalue["directories"].is_object())
            {
                ReadFilesArray(i.value()["files"], *structure);
                ReadDirectoriesArray(i.value()["directories"], *structure);
            }
            else
            {
                throw IOException("Incorrect file structure.");
            }
        }
    }

    static bool FileExists(const std::string &path)
    {
        return (access(path.c_str(), F_OK) == 0);
    }

    std::shared_ptr<ProjectPackage> LoadFromFile(const std::string &path)
    {
        nlohmann::json j;
        std::ifstream file(path);
        try
        {
            file >> j;
        }
        catch(const nlohmann::json::exception &e)
        {
            throw IOException("Invalid file format");
        }

        auto projectPackage = std::make_shared<ProjectPackage>();

        //--- Project Name
        if(j.contains("projectName") && j["projectName"].is_string())
            projectPackage->name = j["projectName"].get<std::string>();
        else
            throw IOException("Project has no name.");

        //--- Project language
        if(j.contains("projectLanguage") && j["projectLanguage"].is_string())
            projectPackage->language = j["projectLanguage"].get<std::string>();
        else
            throw IOException("Project has no language.");

        //--- Project main file
        if(j.contains("projectMain") && j["projectMain"].is_string() && FileExists(j["projectMain"]))
            projectPackage->mainScript = j["projectMain"].get<std::string>();
        else
            throw IOException("Project main is invalid.");

        //--- File structure
        if(j.contains("files") && j["files"].is_array())
            ReadFilesArray(j["files"], projectPackage->fileStructure);
        else
            throw IOException("Incorrect file structure.");

        if(j.contains("directories") && j["directories"].is_object())
            ReadDirectoriesArray(j["directories"], projectPackage->fileStructure);
        else
            throw IOException("Incorrect file structure.");

        return projectPackage;
    }

    //--- Saver

    static nlohmann::json CreateFilesArray(const FileStructure &fileStructure)
    {
        nlohmann::json array = nlohmann::json::array();
        for(const auto& f : fileStructure.files)
        {
            array.push_back(f.Name);
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