//
// Created by Benjam on 15-04-21.
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Object2D.h"

namespace Math4BG
{

    Object2D::Object2D() : m_ib({})
    {

    }

    Object2D::Object2D(std::shared_ptr<Shader> shader, ModelData *model, const Transform& transform, const glm::vec3 &color) :
    m_shader(shader),
    m_transform(transform),

    m_va(),
    m_vb(),
    m_vbl(),
    m_vertices(model->vertices.size()),
    m_indices(model->ibc.Entries()),
    m_ib(model->ibc)
    {
        m_va.Bind();
        m_vb.Add(model->vertices.data(), model->vertices.size() * sizeof(Vertex));
        m_vb.Push();

        m_vbl.Push<float>(3); // Pos
        m_vbl.Push<float>(3); // Color
        m_vbl.Push<float>(2); // Texture coords
        m_vbl.Push<float>(3); // Normals

        m_va.AddBuffer(m_vb, m_vbl);

        m_color = {color, 1.0f};

        UpdateModelMatrix();
    }

    void Object2D::Bind(const ICamera &camera) const
    {
        /*bool hasTexture = false;
        if(m_texture != nullptr)
        {
            m_texture->Bind(0);
            m_texture->Bind(1);
            hasTexture = true;
        }*/

        //---
        m_shader->Bind();
        m_shader->SetUniformMat4("ProjectionMatrix", camera.GetProjectionMatrix());
        m_shader->SetUniformMat4("ViewMatrix", camera.GetView());
        m_shader->SetUniformMat4("ModelMatrix", m_modelMatrix);
        m_shader->SetUniformVec4("vColor", m_color);
        m_shader->SetUniform1i("bTextureExists", /*hasTexture ? 1 :*/ 0);
        m_shader->SetUniformVec3("vCameraPos", camera.GetPos());

        m_va.Bind();

        if(m_indices > 0)
            m_ib.Bind();

        if(m_indices == 0)
            glDrawArrays(GL_TRIANGLES, 0, m_vertices);
        else
            glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        Unbind();
    }

    void Object2D::Unbind() const
    {
        m_va.Unbind();
        m_vb.Unbind();
        m_ib.Unbind();
        m_shader->Unbind();
    }

    void Object2D::UpdateModelMatrix()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_transform.Origin);
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        m_modelMatrix = glm::translate(this->m_modelMatrix, m_transform.Position - m_transform.Origin);
        m_modelMatrix = glm::scale(this->m_modelMatrix, m_transform.Scale);
    }
}