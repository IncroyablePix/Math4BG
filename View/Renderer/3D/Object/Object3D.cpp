//
// Created by Benjam on 13-04-21.
//

#include <iostream>
#include "Object3D.h"
#include "../GL/GLMacros.h"

namespace Math4BG
{
    Object3D::Object3D(std::shared_ptr<Shader> shader, const IndexBufferContainer &ibc, VerticesContainer &vc, const Transform &transform) :
            m_va(std::make_unique<VertexArray>()),
            m_vb(std::make_unique<VertexBuffer>()),
            m_vbl(std::make_unique<VertexBufferLayout>()),
            m_shader(shader),
            m_transform(transform),
            m_vc(vc)
    {
        /*std::cout << "TRANSFORM: " << transform.Position.x << ", " << transform.Position.y << ", " << transform.Position.z << std::endl;
        for(int i = 0; i < m_vc.entries * 3; i += 3) {
            std::cout << "BEF: " << m_vc.ptrData[i] << ", " << m_vc.ptrData[i + 1] << ", " << m_vc.ptrData[i + 2] << std::endl;
            m_vc.ptrData[i] += transform.Position.x;
            m_vc.ptrData[i + 1] += transform.Position.y;
            m_vc.ptrData[i + 2] += transform.Position.z;
        }*/

        vc.ApplyTransform(transform);


        //---HARD CODED
        m_shader->Bind();
        //m_shader->SetUniform4f("vColor", 1.0f, 1.0f, 1.0f, 1.0f);
        m_shader->Unbind();

        for(int i = 0; i < vc.entries * 3; i += 3) {
            std::cout << "AFT: " << vc.ptrData[i] << ", " << vc.ptrData[i + 1] << ", " << vc.ptrData[i + 2] << std::endl;
        }

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

    void Object3D::SetPos(const glm::vec3 position)
    {
        m_transform.Position = position;
        m_vc.ApplyTransform(m_transform);

        m_vb->Clear();
        m_vb->Add(m_vc.ptrData, m_vc.size);
        //m_vb->Push();
        //m_vb->Push();
        //m_vb->Rebind(m_vc.ptrData, m_vc.size);
        //m_vb->Rebind();
    }
}