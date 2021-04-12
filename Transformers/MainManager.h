//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_MAINMANAGER_H
#define ARCPOSITION_MAINMANAGER_H

#include <cstdint>
#include "World.h"

enum WorldType : uint32_t
{
    FlatWorld
};

class MainManager : std::enable_shared_from_this<MainManager>
{
public:
    MainManager();
    ~MainManager();

private:
    std::unordered_map<int, World>;
};


#endif //ARCPOSITION_MAINMANAGER_H
