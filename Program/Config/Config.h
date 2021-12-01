//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONFIG_H
#define ARCPOSITION_CONFIG_H

#define CONFIG_PATH         ("settings.cfg")

#include <string>
#include <memory>

namespace Math4BG
{
    struct Config : public std::enable_shared_from_this<Config>
    {
        std::string projectPackage;
        bool fpsLimiter;
    };

    void LoadConfig(const std::string &path, const std::shared_ptr<Config>& config);
    void SaveConfig(const std::string &path, const std::shared_ptr<Config>& config);
    void ParseArgs(int argc, char** argv, std::shared_ptr<Config> config);
}

#endif //ARCPOSITION_CONFIG_H
