//
// Created by Benjam on 16-02-21.
//

#include <iostream>
#include "VertexBufferLayout.h"


namespace Math4BG
{
    VertexBufferLayout::VertexBufferLayout() : m_stride(0)
    {

    }

    unsigned int VertexBufferLayout::GetStride() const
    {
        return m_stride;
    }

    std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const &
    {
        return m_elements;
    }

    VertexBufferLayout::~VertexBufferLayout()
    = default;
}