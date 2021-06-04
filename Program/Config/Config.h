//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONFIG_H
#define ARCPOSITION_CONFIG_H

#define CONFIG_PATH         ("settings.cfg")

#include <string>


namespace Math4BG
{
    struct Config
    {
        std::string scriptFile;
        bool fpsLimiter;
    };

    void LoadConfig(const std::string &path, Config &config);
    void ParseArgs(int argc, char** argv, Config &config);
}

#endif //ARCPOSITION_CONFIG_H
