//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <sstream>
#include "Config.h"
#include "../../Transformers/Interpreter/LuaInterpreter.h"

namespace Math4BG
{
    void SetConfigScript(const std::string &scriptName, Config &config)
    {
        std::ostringstream ss;
        ss << "scripts/" << scriptName << ".lua";
        config.scriptFile = ss.str();
    }

    void LoadConfig(const std::string &path, Config &config)
    {
        LuaInterpreter lua(nullptr, nullptr);

        lua.ExecuteFile(path);
        std::string scriptName = lua.GetString("script");
        SetConfigScript(scriptName, config);
        config.fpsLimiter = lua.GetBool("fpslimiter");
    }

    void ParseArgs(int argc, char** argv, Math4BG::Config &config)
    {
        std::string previous;
        for(int i = 1; i < argc; i ++)
        {
            if(previous == "-s")
            {
                SetConfigScript(argv[i], config);
            }

            previous = argv[i];
        }
    }
}

