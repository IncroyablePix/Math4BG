//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONFIG_H
#define ARCPOSITION_CONFIG_H

#define CONFIG_PATH         ("settings.cfg")

#include <string>
struct Config
{
    std::string scriptFile;
};

void LoadConfig(const std::string& path, Config& config);

#endif //ARCPOSITION_CONFIG_H
