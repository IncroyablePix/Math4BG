//
// Created by Benjam on 22-05-21.
//

#include <GL/glew.h>
#include "Texture.h"

namespace Math4BG
{

    Texture::Texture(unsigned int type) : m_type(type)
    {
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);
    }

    void Texture::Bind(unsigned int textureUnit)
    {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(m_type, m_id);
    }

    void Texture::Unbind()
    {
        glActiveTexture(0);
        glBindTexture(m_type, 0);
    }
}