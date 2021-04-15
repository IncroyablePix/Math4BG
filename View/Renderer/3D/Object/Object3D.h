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
#include <memory>

namespace Math4BG
{
    class Object3D : public IDrawable
    {
    public:
        Object3D(std::shared_ptr<Shader> shader, const IndexBufferContainer &ibc);
        ~Object3D();

        void Bind() const;
        void Unbind() const;

    private:
        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<VertexBufferLayout> m_vbl;
        std::unique_ptr<IndexBuffer> m_ib;
        std::shared_ptr<Shader> m_shader;
    };
}

#endif //MATH4BG_OBJECT3D_H
