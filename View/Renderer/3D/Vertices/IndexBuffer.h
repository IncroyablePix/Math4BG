//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_INDEXBUFFER_H
#define MATH4BG_INDEXBUFFER_H

#include <iostream>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "../../../../Physics/Transform.h"

namespace Math4BG
{
    struct IndexBufferContainer
    {
        IndexBufferContainer() = default;
        IndexBufferContainer(const unsigned int* indices, unsigned int len)
        {
            for(int i = 0; i < len; i ++)
                vertices.push_back(indices[i]);
        }

        std::vector<unsigned int> vertices;

        /*unsigned int* indices;
        int count;*/

        inline void Push(const unsigned int i) { vertices.push_back(i); }
        inline void Push(const unsigned int i1, const unsigned int i2, const unsigned int i3) { vertices.push_back(i1); vertices.push_back(i2); vertices.push_back(i3); }
        inline const unsigned int* Data() const { return vertices.data(); }
        inline unsigned int Entries() const { return vertices.size(); }
        inline unsigned int GetSize() const { return sizeof(unsigned int) * vertices.size(); }
    };

    struct VerticesContainer
    {
        VerticesContainer() = default;
        VerticesContainer(const float *array, unsigned int len)
        {
            for(int i = 0; i < len; i ++)
                vertices.push_back(array[i]);
        }

        std::vector<float> vertices;

        inline void Push(const glm::vec3 &v3) { vertices.push_back(v3.x); vertices.push_back(v3.y); vertices.push_back(v3.z); }
        inline float* Data() { return vertices.data(); }
        inline unsigned int GetSize() const { return sizeof(float) * vertices.size(); }
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
