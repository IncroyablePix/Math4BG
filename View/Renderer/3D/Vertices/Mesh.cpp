//
// Created by Benjam on 20-05-21.
//

#include "Mesh.h"

namespace Math4BG
{
    Mesh::Mesh(Vertex* vertices, int verticesSize, IndexBufferContainer& ibc, const Transform& transform):
    //Mesh::Mesh(std::vector<Vertex> vertices, IndexBufferContainer& indices, Transform& transform) :
    m_transform(transform),

    m_va(std::make_unique<VertexArray>()),
    m_vb(std::make_unique<VertexBuffer>()),
    m_vbl(std::make_unique<VertexBufferLayout>()),
    m_vertices(verticesSize),
    m_indices(ibc.Entries())
    {
        std::cout << ibc.Entries() << " - " << ibc.GetSize() << std::endl;
        std::cout << sizeof(Vertex) << " - " << verticesSize << " - " << verticesSize * sizeof(Vertex) << std::endl;
        m_va->Bind();
        m_vb->Add(vertices, verticesSize * sizeof(Vertex));
        m_vb->Push();

        m_vbl->Push<float>(3); // Pos
        m_vbl->Push<float>(3); // Color
        m_vbl->Push<float>(2); // Texture coords
        m_vbl->Push<float>(3); // Normals // TODO: Vérifier
        //m_vbl->Push<float>(11);

        m_va->AddBuffer(*m_vb, *m_vbl);

        if(m_indices > 0)
            m_ib = std::make_unique<IndexBuffer>(ibc);

        UpdateModelMatrix();


        /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, col));
        glEnableVertexAttribArray(1);
        //Texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(2);
        //Normal
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);*/
    }

    void Mesh::UpdateModelMatrix()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_transform.Origin);
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_modelMatrix = glm::rotate(this->m_modelMatrix, glm::radians(m_transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        m_modelMatrix = glm::translate(this->m_modelMatrix, m_transform.Position - m_transform.Origin);
        m_modelMatrix = glm::scale(this->m_modelMatrix, m_transform.Scale);

        // TODO : Call from Object3D when model is updated
    }

    void Mesh::Bind(MainCamera *camera, Shader& shader, bool hasTexture, const glm::vec4 &color) const
    {
        shader.Bind();
        shader.SetUniformMat4("ProjectionMatrix", camera->GetProjectionMatrix());
        shader.SetUniformMat4("ViewMatrix", camera->GetView());
        shader.SetUniformMat4("ModelMatrix", m_modelMatrix);
        shader.SetUniformVec4("vColor", color);
        shader.SetUniform1i("bTextureExists", hasTexture ? 1 : 0);
        shader.SetUniformVec3("vCameraPos", camera->GetPos());

        m_va->Bind();

        if(m_indices > 0)
            m_ib->Bind();

        if(m_indices == 0)
            glDrawArrays(GL_TRIANGLES, 0, m_vertices);
        else
            glDrawElements(GL_TRIANGLES, m_ib->GetCount(), GL_UNSIGNED_INT, nullptr);

        /*glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);*/

        Unbind(shader);
    }

    void Mesh::Unbind(Shader& shader) const
    {
        m_va->Unbind();
        m_vb->Unbind();
        m_ib->Unbind();
        shader.Unbind();
    }

    void Mesh::SetPos(const glm::vec3 &position)
    {
        m_transform.Position = position;
        UpdateModelMatrix();
    }

    void Mesh::SetOrigin(const glm::vec3 &position)
    {
        m_transform.Origin = position;
        UpdateModelMatrix();
    }

    void Mesh::SetScale(const glm::vec3 &scale)
    {
        m_transform.Scale = scale;
        UpdateModelMatrix();
    }

    void Mesh::SetRotation(const glm::vec3 &rotation)
    {
        m_transform.Rotation = rotation;
        UpdateModelMatrix();
    }
}