//
// Created by Benjam on 26-05-21.
//

#include <GL/glew.h>
#include "RenderedTexture.h"
#include "../../GL/GLMacros.h"

namespace Math4BG
{
    RenderedTexture::RenderedTexture(unsigned int width, unsigned int height) : Texture(GL_TEXTURE_2D), m_regenMipMaps(true)
    {
        GLCall(glGenTextures(1, &m_id));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_id, 0));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, nullptr));
    }

    RenderedTexture::~RenderedTexture()
    {
        GLCall(glDeleteTextures(1, &m_id));
    }

    void RenderedTexture::Bind(unsigned int textureUnit)
    {
        Texture::Bind(textureUnit);
        glBindSampler(textureUnit, m_sampler);
        glClearDepth(1.0);

        if(m_regenMipMaps)
            glGenerateMipmap(GL_TEXTURE_2D);
    }

    void RenderedTexture::SetRegenMipMaps(bool b)
    {
        m_regenMipMaps = b;
    }
}