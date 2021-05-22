//
// Created by Benjam on 20-05-21.
//

#ifndef MATH4BG_MESH_H
#define MATH4BG_MESH_H

#include <vector>
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "../Camera/MainCamera.h"
#include "IndexBuffer.h"
#include "../Shaders/Shader.h"

namespace Math4BG
{
    class Mesh
    {
    public:
        Mesh(Vertex* vertices, int verticesSize, IndexBufferContainer& ibc, const Transform& transform);

        void Bind(MainCamera* camera, Shader&, bool hasTexture, const glm::vec4 &color) const;
        void Unbind(Shader& shader) const;

        void UpdateModelMatrix();
        void SetPos(const glm::vec3 &position);
        void SetOrigin(const glm::vec3 &position);
        void SetScale(const glm::vec3 &scale);
        void SetRotation(const glm::vec3 &rotation);

    private:
        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<IndexBuffer> m_ib;
        std::unique_ptr<VertexBufferLayout> m_vbl;

        unsigned int m_vertices;
        unsigned int m_indices;

        Transform m_transform;

        glm::mat4 m_modelMatrix;
    };
}

#endif //MATH4BG_MESH_H
