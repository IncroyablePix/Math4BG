//
// Created by Benjam on 18-05-21.
//

#ifndef MATH4BG_IMODELLOADER_H
#define MATH4BG_IMODELLOADER_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "../View/Renderer/OG33Renderer.h"
#include "../IO/ModelData.h"

namespace Math4BG
{
    class IModelLoader
    {
    public:
        virtual ModelData LoadModel(const std::string &path) = 0;
    };
}

#endif //MATH4BG_IMODELLOADER_H
