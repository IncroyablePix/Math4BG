//
// Created by Benjam on 18-05-21.
//

#ifndef MATH4BG_OBJLOADER_H
#define MATH4BG_OBJLOADER_H


#include "IModelLoader.h"

namespace Math4BG
{
    class OBJLoader : IModelLoader
    {
        ModelData LoadModel(const std::string &path) override;
    };
}



#endif //MATH4BG_OBJLOADER_H
