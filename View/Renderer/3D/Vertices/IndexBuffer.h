//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_INDEXBUFFER_H
#define MATH4BG_INDEXBUFFER_H

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include "../../../../Physics/Transform.h"

namespace Math4BG
{
    struct IndexBufferContainer
    {
        unsigned int* indices;
        int count;

        ~IndexBufferContainer()
        {
            delete[] indices;
        }
    };

    struct VerticesContainer
    {
        float *ptrData;
        unsigned int entries;
        unsigned int size;

        inline void ApplyTransform(const Transform& transform)
        {
            for(int i = 0; i < entries * 3; i += 3) {
                std::cout << "BEF: " << ptrData[i] << ", " << ptrData[i + 1] << ", " << ptrData[i + 2] << std::endl;
                (ptrData[i]) += transform.Position.x;
                ptrData[i + 1] += transform.Position.y;
                ptrData[i + 2] += transform.Position.z;
            }
        }

        ~VerticesContainer()
        {
            delete[] ptrData;
        }
    };

    class IndexBuffer : public std::enable_shared_from_this<IndexBuffer>
    {
    public:
        IndexBuffer(const IndexBufferContainer &ibc);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return m_count; }

    private:
        unsigned int m_rendererId;
        unsigned int m_count;
    };
}

#endif //MATH4BG_INDEXBUFFER_H
