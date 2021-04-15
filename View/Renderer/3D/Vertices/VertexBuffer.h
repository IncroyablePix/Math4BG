//
// Created by Benjam on 13-02-21.
//

#ifndef INC_3D_GAME_ENGINE_VERTEXBUFFER_H
#define INC_3D_GAME_ENGINE_VERTEXBUFFER_H

#include <vector>
#include <GL/glew.h>
#include <memory>

namespace Math4BG
{
    class VertexBuffer : public std::enable_shared_from_this<VertexBuffer>
    {
    public:
        VertexBuffer();

        VertexBuffer(const void *data, unsigned int size);

        ~VertexBuffer();

        void Bind() const;

        void Rebind(const void *data, unsigned int size) const;

        void Unbind() const;

        void Add(void *ptrData, unsigned int size);

        void Clear();

        void Push();

    private:
        unsigned int m_rendererID;
        std::vector<unsigned char> m_data;

        void Repush();
    };
}


#endif //INC_3D_GAME_ENGINE_VERTEXBUFFER_H
