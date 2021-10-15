//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_OBJECT3D_H
#define MATH4BG_OBJECT3D_H

#include "../Texture/Texture.h"
#include "../Vertices/Mesh.h"
#include "../Vertices/VertexBufferLayout.h"
#include "../Vertices/VertexBuffer.h"
#include "../Vertices/VertexArray.h"
#include "../Shaders/Shader.h"
#include "../Vertices/IndexBuffer.h"
#include "../../Draw/IDrawable.h"
#include "../Camera/ICamera.h"
#include "../Camera/MainCamera.h"
#include "../../../../Physics/Transform.h"
#include "../../../../IO/IModelLoader.h"
#include "../../../../IO/ModelData.h"
#include <memory>

namespace Math4BG
{
    class Object3D : public IDrawable
    {
    public:
        Object3D(std::shared_ptr<Shader> shader, ModelData* model, const Transform &transform);
        ~Object3D();

        //void SetShaderAttribute(std::string name);

        void Bind(const ICamera &camera) const override;
        void Unbind() const override;

        void SetPos(const glm::vec3 position);
        void SetOrigin(const glm::vec3 position);
        void SetScale(const glm::vec3 scale);
        void SetRotation(const glm::vec3 rotation);

        void SetTexture(std::shared_ptr<Texture> texture);

    private:
        Transform m_transform;
        std::shared_ptr<Texture> m_texture;

        std::vector<std::unique_ptr<Mesh>> m_meshes;
        std::shared_ptr<Shader> m_shader;
    };
}

#endif //MATH4BG_OBJECT3D_H
