//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <sstream>
#include "Config.h"
#include "../../Transformers/Interpreter/LuaInterpreter.h"
#include <fstream>
#include "../../IO/Json/json.hpp"

namespace Math4BG
{
    void SetConfigScript(const std::string &scriptName, Config &config)
    {
        /*std::ostringstream ss;
        ss << "scripts/" << scriptName << ".lua";
        config.scriptFile = ss.str();*/
    }

    void LoadConfig(const std::string &path, const std::shared_ptr<Config>& config)
    {
        nlohmann::json j;
        std::ifstream file(path);
        file >> j;

        if(j.contains("project") && j["project"].is_string())
            config->projectPackage = j["project"];
        else
            config->projectPackage = "";

        //---

        if(j.contains("fpsLimiter") && j["fpsLimiter"].is_boolean())
            config->fpsLimiter = j["fpsLimiter"];
        else
            config->fpsLimiter = true;
    }

    void SaveConfig(const std::string &path, const std::shared_ptr<Config>& config)
    {
        nlohmann::json j = nlohmann::json::object();
        j["project"] = config->projectPackage;
        j["fpsLimiter"] = config->fpsLimiter;

        std::ofstream file(path);
        file << j;
    }

    void ParseArgs(int argc, char** argv, std::shared_ptr<Config> config)
    {
        std::string previous;
        /*for(int i = 1; i < argc; i ++)
        {
            if(previous == "-s")
            {
                SetConfigScript(argv[i], config);
            }

            previous = argv[i];
        }*/
    }
}

