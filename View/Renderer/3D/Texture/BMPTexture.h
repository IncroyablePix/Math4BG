//
// Created by Benjam on 22-05-21.
//

#ifndef MATH4BG_BMPTEXTURE_H
#define MATH4BG_BMPTEXTURE_H

#include "Texture.h"

namespace Math4BG
{
    class BMPTexture : public Texture
    {
    public:
        BMPTexture(const std::string &path, unsigned int type);

    private:
        unsigned char *LoadBMP(const std::string &imagePath);
    };
}

#endif //MATH4BG_BMPTEXTURE_H
