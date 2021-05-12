//
// Created by Benjam on 13-02-21.
//

#include <iostream>
#include "VertexBuffer.h"
#include "../GL/GLMacros.h"


namespace Math4BG
{
    VertexBuffer::VertexBuffer() : m_rendererID(0)
    {
        glGenBuffers(1, &m_rendererID);
        Bind();
    }

    VertexBuffer::VertexBuffer(const void *data, unsigned int size) : m_rendererID(0)
    {
        glGenBuffers(1, &m_rendererID);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_rendererID);
    }

    void VertexBuffer::Add(void *ptrData, unsigned int size)
    {
        m_data.insert(m_data.end(), (unsigned char *) ptrData, (unsigned char *) ptrData + size);
    }

    void VertexBuffer::Clear()
    {
        m_data.clear();
    }

    void VertexBuffer::Push()
    {
        //std::cout << "sizeof buffer : " << m_data.size() << std::endl;
        glBufferData(GL_ARRAY_BUFFER, m_data.size(), &m_data[0], GL_STATIC_DRAW);
    }

    void VertexBuffer::Repush()
    {
        glBufferData(GL_ARRAY_BUFFER, m_data.size(), &m_data[0], GL_STATIC_DRAW);
        Bind();
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Rebind(const void *data, unsigned int size) const
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        Bind();
    }
}