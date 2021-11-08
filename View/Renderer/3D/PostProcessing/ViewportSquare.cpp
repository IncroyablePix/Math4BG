//
// Created by Benjam on 27-05-21.
//

#include "ViewportSquare.h"
#include "../Shaders/Shader.h"

namespace Math4BG
{
    ViewportSquare::ViewportSquare()
    {
        m_va.Bind();
        m_vb.Add((void *) fullSquare, 6 * sizeof(Vertex));
        m_vb.Push();

        m_vbl.Push<float>(3); // Pos
        m_vbl.Push<float>(3); // Color
        m_vbl.Push<float>(2); // Texture coords
        m_vbl.Push<float>(3); // Normals

        m_va.AddBuffer(m_vb, m_vbl);
    }

    void ViewportSquare::Bind(Shader& shader, Texture& texture) const
    {
        shader.Bind();

        texture.Bind(0);
        texture.Bind(1);

        m_va.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        Unbind(shader);
    }

    void ViewportSquare::Unbind(Shader& shader) const
    {
        m_va.Unbind();
        m_vb.Unbind();

        shader.Unbind();
    }

    ViewportSquare::~ViewportSquare()
    = default;
}