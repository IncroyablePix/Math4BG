//
// Created by Benjam on 26-05-21.
//

#include <GL/glew.h>
#include "FrameBufferObject.h"
#include "../../GL/GLMacros.h"

namespace Math4BG
{
    FrameBufferObject::FrameBufferObject(unsigned int width, unsigned int height) :
    m_width(width),
    m_height(height)
    {
        //--- COLOR
        GLCall(glGenFramebuffers(1, &m_colBuffer));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_colBuffer));

        m_texture = std::make_shared<RenderedTexture>(width, height);

        //--- DEPTH
        GLCall(glGenRenderbuffers(1, &m_depthBuffer));
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer));
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height));
        GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer));
    }

    FrameBufferObject::~FrameBufferObject()
    {
        GLCall(glDeleteRenderbuffers(1, &m_colBuffer));
        GLCall(glDeleteRenderbuffers(1, &m_depthBuffer));
    }

    void FrameBufferObject::Bind(bool fullViewport) const
    {
        /*glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_colBuffer));
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_depthBuffer));
        if(fullViewport)
            glViewport(0, 0, m_width, m_height);

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));
    }

    void FrameBufferObject::Unbind() const
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    //void FrameBufferObject::BindFramebufferTexture()

    bool FrameBufferObject::IsComplete() const
    {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
}