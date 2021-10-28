//
// Created by Benjam on 22-05-21.
//

#ifndef MATH4BG_TEXTURE_H
#define MATH4BG_TEXTURE_H

#include <string>

namespace Math4BG
{
    class Texture
    {
    public:
        explicit Texture(unsigned int type);
        virtual ~Texture();

        inline unsigned int GetId() const { return m_id; }

        virtual void Bind(unsigned int textureUnit);
        void Unbind();

    protected:
        unsigned int m_id;
        unsigned int m_sampler;
        unsigned int m_type;
        int m_width = 0;
        int m_height = 0;
    };
}

#endif //MATH4BG_TEXTURE_H
