//
// Created by Benjam on 27-05-21.
//

#ifndef MATH4BG_VIEWPORTSQUARE_H
#define MATH4BG_VIEWPORTSQUARE_H


#include "../Vertices/VertexArray.h"
#include "../Vertices/IndexBuffer.h"
#include "../Vertices/VertexBufferLayout.h"
#include "../Shaders/Shader.h"
#include "../Texture/Texture.h"

namespace Math4BG
{
    class ViewportSquare
    {
    public:
        ViewportSquare();
        ~ViewportSquare();

        void Bind(Math4BG::Shader &shader, Texture& texture) const;

    private:
        VertexArray m_va;
        VertexBuffer m_vb;
        VertexBufferLayout m_vbl;

        void Unbind(Shader& shader) const;
    };

    const static Vertex fullSquare[] =
    {
        {{-1.0, -1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},// top 1
        {{1.0, 1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0, 1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

        {{1.0, -1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top 2
        {{1.0, 1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0, -1.0, 0.0}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}
    };
}

#endif //MATH4BG_VIEWPORTSQUARE_H
