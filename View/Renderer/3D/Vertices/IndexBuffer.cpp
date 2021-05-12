//
// Created by Benjam on 13-04-21.
//

#include "IndexBuffer.h"
#include "../GL/GLMacros.h"
#include <GL/glew.h>

namespace Math4BG
{
    IndexBuffer::IndexBuffer(const IndexBufferContainer& ibc) :
    m_count(ibc.count)
    {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        glGenBuffers(1, &m_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibc.count * sizeof(unsigned int), ibc.indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_rendererId);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}