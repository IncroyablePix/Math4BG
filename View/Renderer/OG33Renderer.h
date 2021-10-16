//
// Created by Benjam on 10/16/2021.
//

#ifndef MATH4BG_OG33RENDERER_H
#define MATH4BG_OG33RENDERER_H


#include <memory>
#include "3D/Camera/ICamera.h"
#include "Draw/IDrawable.h"
#include <GL/glew.h>

namespace Math4BG
{
    class OG33Renderer : public std::enable_shared_from_this<OG33Renderer>
    {
    public:
        OG33Renderer(int width, int height);
        ~OG33Renderer();

        inline unsigned int Width() const { return m_width; }
        inline unsigned int Height() const { return m_height; }

        void Resize(int width, int height);

        virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b);
        virtual void Draw(ICamera* camera, IDrawable* drawable);
        virtual void Clear();

        static std::shared_ptr<OG33Renderer> Create(int width, int height);
    private:
        int m_width;
        int m_height;

        glm::vec4 m_background { 0.0f, 0.0f, 0.0f, 0.0f };

        static float Col(uint32_t color);
    };
}

#endif //MATH4BG_OG33RENDERER_H
