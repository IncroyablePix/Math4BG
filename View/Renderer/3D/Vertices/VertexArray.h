//
// Created by Benjam on 16-02-21.
//

#ifndef INC_3D_GAME_ENGINE_VERTEXARRAY_H
#define INC_3D_GAME_ENGINE_VERTEXARRAY_H

#include "VertexBuffer.h"
#include <GL/glew.h>

#include <memory>

namespace Math4BG
{
    class VertexBufferLayout; // Forward to avoid cyclic include
    class VertexArray : public std::enable_shared_from_this<VertexArray>
    {
    public:
        VertexArray();

        ~VertexArray();

        void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;

        void Bind() const;

        void Unbind() const;

    private:
        unsigned int m_rendererID{};
    };
}

#endif //INC_3D_GAME_ENGINE_VERTEXARRAY_H
