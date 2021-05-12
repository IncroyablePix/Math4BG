//
// Created by Benjam on 16-02-21.
//

#ifndef INC_3D_GAME_ENGINE_VERTEXBUFFERLAYOUT_H
#define INC_3D_GAME_ENGINE_VERTEXBUFFERLAYOUT_H

#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <memory>

namespace Math4BG
{
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT:
                    return 4;
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
            }
            //ASSERT(false);
            return 0;
        }
    };

    class VertexBufferLayout : public std::enable_shared_from_this<VertexBufferLayout>
    {
    public:
        VertexBufferLayout();

        template<typename T>
        void Push(unsigned int count)
        {
            //static_assert(false, "Nope.");
        }

        unsigned int GetStride() const;

        std::vector<VertexBufferElement> GetElements() const &;

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride;
    };

    template<>
    inline void VertexBufferLayout::Push<float>(unsigned int count)
    {
        m_elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
    {
        m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
    {
        m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
}

#endif //INC_3D_GAME_ENGINE_VERTEXBUFFERLAYOUT_H
