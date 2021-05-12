//
// Created by Benjam on 13-04-21.
//

#include "IndexBuffer.h"
#include "../GL/GLMacros.h"
#define GLEW_STATIC
#include <GL/glew.h>

namespace Math4BG
{
    IndexBuffer::IndexBuffer(const IndexBufferContainer& ibc) :
    m_count(ibc.count)
    {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        GLCall(glGenBuffers(1, &m_rendererId));
        (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibc.count * sizeof(unsigned int), ibc.indices, GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer()
    {
        GLCall(glDeleteBuffers(1, &m_rendererId));
    }

    void IndexBuffer::Bind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    }

    void IndexBuffer::Unbind() const
    {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}