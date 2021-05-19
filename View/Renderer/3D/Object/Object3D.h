//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_OBJECT3D_H
#define MATH4BG_OBJECT3D_H

#include "../Vertices/VertexBufferLayout.h"
#include "../Vertices/VertexBuffer.h"
#include "../Vertices/VertexArray.h"
#include "../Shaders/Shader.h"
#include "../Vertices/IndexBuffer.h"
#include "../../Draw/IDrawable.h"
#include "../Camera/ICamera.h"
#include "../Camera/MainCamera.h"
#include "../../../../Physics/Transform.h"
#include <memory>

namespace Math4BG
{
    class Object3D : public IDrawable
    {
    public:
        Object3D(std::shared_ptr<Shader> shader, const IndexBufferContainer &ibc, VerticesContainer &vc, const Transform &transform);
        ~Object3D();

        //void SetShaderAttribute(std::string name);

        void Bind(MainCamera* camera) const;
        void Unbind() const;

        void SetPos(const glm::vec3 position);

    private:
        Transform m_transform;
        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<VertexBufferLayout> m_vbl;
        std::unique_ptr<IndexBuffer> m_ib;
        std::shared_ptr<Shader> m_shader;

        VerticesContainer m_vc;
    };
}

#endif //MATH4BG_OBJECT3D_H
