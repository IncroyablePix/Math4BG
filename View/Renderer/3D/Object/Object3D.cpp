//
// Created by Benjam on 13-04-21.
//

#include <iostream>
#include "Object3D.h"
#include "../GL/GLMacros.h"

namespace Math4BG
{
    Object3D::Object3D(std::shared_ptr<Shader> shader, ModelData *model, const Transform &transform) :
        m_shader(shader),
        m_transform(transform)
    {
        m_meshes.push_back(std::make_unique<Mesh>((Vertex*) (model->vertices.data()), model->vertices.size(), model->ibc, transform));
    }

    Object3D::~Object3D()
    {

    }

    void Object3D::Bind(MainCamera* camera) const
    {
        for(auto& mesh : m_meshes)
            mesh->Bind(camera, *m_shader);

    }

    void Object3D::Unbind() const
    {
    }

    void Object3D::SetPos(const glm::vec3 position)
    {
        m_transform.Position = position;

        //---TODO : Set as an overlay
        for(auto& mesh : m_meshes)
            mesh->SetPos(position);
    }

    void Object3D::SetOrigin(const glm::vec3 position)
    {
        m_transform.Origin = position;

        //---TODO : Set as an overlay
        for(auto& mesh : m_meshes)
            mesh->SetOrigin(position);
    }

    void Object3D::SetRotation(const glm::vec3 rotation)
    {
        m_transform.Rotation = rotation;

        //---TODO : Set as an overlay
        for(auto& mesh : m_meshes)
            mesh->SetRotation(rotation);
    }

    void Object3D::SetScale(const glm::vec3 scale)
    {
        m_transform.Scale = scale;

        //---TODO : Set as an overlay
        for(auto& mesh : m_meshes)
            mesh->SetScale(scale);
    }
}