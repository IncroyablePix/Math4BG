//
// Created by Benjam on 13-04-21.
//

#include <iostream>
#include "Object3D.h"
#include "../GL/GLMacros.h"

namespace Math4BG
{
    Object3D::Object3D(std::shared_ptr<Shader> shader, const IndexBufferContainer &ibc) :
            m_va(std::make_unique<VertexArray>()),
            m_vb(std::make_unique<VertexBuffer>()),
            m_vbl(std::make_unique<VertexBufferLayout>()),
            m_shader(shader)
    {
        m_va->Bind();
        m_vb->Add((new float[24]
                {
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,

                        0.5f, 0.5f, 0.0f,
                        -0.5f, 0.5f, 0.0f,

                        -0.5f, -0.5f, -1.0f,
                        0.5f, -0.5f, -1.0f,

                        0.5f, 0.5f, -1.0f,
                        -0.5f, 0.5f, -1.0f
                }), sizeof(float) * 8 * 3);
        m_vb->Push();

        m_vbl->Push<float>(3);
        m_va->AddBuffer(*m_vb, *m_vbl);

        m_ib = std::make_unique<IndexBuffer>(ibc);
    }

    Object3D::~Object3D()
    {

    }

    void Object3D::Bind() const
    {
        m_shader->Bind();
        m_va->Bind();
        m_ib->Bind();

        std::cout << m_ib->GetCount() << std::endl;
        glDrawElements(GL_TRIANGLES, m_ib->GetCount(), GL_UNSIGNED_INT, nullptr);

        Unbind();
    }

    void Object3D::Unbind() const
    {
        m_va->Unbind();
        m_vb->Unbind();
        m_ib->Unbind();
        m_shader->Unbind();
    }
}