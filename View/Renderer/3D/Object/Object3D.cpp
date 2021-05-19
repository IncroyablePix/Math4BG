//
// Created by Benjam on 13-04-21.
//

#include <iostream>
#include "Object3D.h"
#include "../GL/GLMacros.h"

namespace Math4BG
{
    Object3D::Object3D(std::shared_ptr<Shader> shader, const IndexBufferContainer &ibc, const VerticesContainer &vc) :
            m_va(std::make_unique<VertexArray>()),
            m_vb(std::make_unique<VertexBuffer>()),
            m_vbl(std::make_unique<VertexBufferLayout>()),
            m_shader(shader)
    {
        //---HARD CODED
        m_shader->Bind();
        //m_shader->SetUniform4f("vColor", 1.0f, 1.0f, 1.0f, 1.0f);
        m_shader->Unbind();

        m_va->Bind();
        m_vb->Add(vc.ptrData, vc.size);
        m_vb->Push();

        m_vbl->Push<float>(3);
        m_va->AddBuffer(*m_vb, *m_vbl);

        m_ib = std::make_unique<IndexBuffer>(ibc);
    }

    Object3D::~Object3D()
    {

    }

    void Object3D::Bind(MainCamera* camera) const
    {
        m_shader->Bind();

        /*m_shader->SetUniformMat4("projectionMatrix", camera->GetProjectionMatrix());// Projection perspective
        m_shader->SetUniformMat4("modelViewMatrix", camera->GetModelViewMatrix());
        m_shader->SetUniformMat4("normalMatrix", camera->GetNormalMatrix());*/

        m_shader->SetUniformMat4("MVP", camera->GetMVP());

        m_va->Bind();
        m_ib->Bind();

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