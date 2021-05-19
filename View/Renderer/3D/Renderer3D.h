//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_RENDERER3D_H
#define MATH4BG_RENDERER3D_H

#include "../IRenderer.h"
#include "Shaders/Shader.h"
#include "Vertices/VertexBufferLayout.h"
#include "Vertices/VertexArray.h"
#include "Object/Object3D.h"
#include <memory>


namespace Math4BG
{
    class Renderer3D : public IRenderer
    {
    public:
        Renderer3D(SDL_Window *window, unsigned int width, unsigned int height);

        ~Renderer3D() override;

        static std::shared_ptr<Renderer3D> Create(SDL_Window *window, unsigned int width, unsigned int height);

        void Draw(MainCamera* camera, IDrawable *drawable) override;
        void SwapBuffers() override;
        void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b) override;

        void Clear() override;

    private:
        SDL_GLContext m_glContext;
        SDL_Window *m_window;

        static float Col(uint32_t color);
        static void GlewInitAttempt();
    };

    static bool glewInitialized = false;
}

#endif //MATH4BG_RENDERER3D_H
