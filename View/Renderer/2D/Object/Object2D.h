//
// Created by Benjam on 15-04-21.
//

#ifndef MATH4BG_OBJECT2D_H
#define MATH4BG_OBJECT2D_H

#include <cstdint>
#include <SDL2/SDL.h>
#include "Point.h"
#include "../../Draw/IDrawable.h"
#include "../../3D/Vertices/VertexBufferLayout.h"
#include "../../3D/Vertices/VertexBuffer.h"
#include "../../3D/Vertices/IndexBuffer.h"
#include "../../3D/Vertices/VertexArray.h"
#include "../../../../IO/ModelData.h"
#include "../../3D/Shaders/Shader.h"

namespace Math4BG
{
    class Object2D : public IDrawable
    {
    public:
        Object2D();
        Object2D(std::shared_ptr<Shader> shader, ModelData *model, const Transform& transform, const glm::vec3 &color);
        ~Object2D() override = default;

        void UpdateModelMatrix();
        void Bind(const ICamera &camera) const override;
        void Unbind() const override;

        //virtual void Draw(SDL_Surface* surface, const Point &size) = 0;

    protected:
        std::shared_ptr<Shader> m_shader;
        VertexArray m_va;
        IndexBuffer m_ib;
        VertexBuffer m_vb;
        VertexBufferLayout m_vbl;

        unsigned int m_vertices;
        unsigned int m_indices;

        Transform m_transform;

        glm::mat4 m_modelMatrix;

        //void SetPixel(SDL_Surface* surface, Point size, int x, int y);
        //static void ny(int &y, const Point &size);
    };
}

#endif //MATH4BG_OBJECT2D_H
