//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_INDEXBUFFER_H
#define MATH4BG_INDEXBUFFER_H

#include <memory>

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
