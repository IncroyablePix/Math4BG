//
// Created by Benjam on 26-05-21.
//

#ifndef MATH4BG_RENDEREDTEXTURE_H
#define MATH4BG_RENDEREDTEXTURE_H

#include "../Texture.h"

namespace Math4BG
{
    class RenderedTexture : public Texture
    {
    public:
        RenderedTexture(unsigned int width, unsigned int height);
        ~RenderedTexture();
        void Bind(unsigned int textureUnit) override;
        void SetRegenMipMaps(bool b);

    private:
        bool m_regenMipMaps;
    };
}

#endif //MATH4BG_RENDEREDTEXTURE_H
