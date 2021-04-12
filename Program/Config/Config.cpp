//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <sstream>
#include "Config.h"
#include "../../Transformers/LuaInterpreter.h"

void LoadConfig(const std::string& path, Config& config)
{
    std::ostringstream ss;
    LuaInterpreter lua;

    lua.ExecuteFile(path);
    std::string scriptName = lua.GetString("script");
    ss << "scripts/" << scriptName << ".lua";
    config.scriptFile = ss.str();
}

