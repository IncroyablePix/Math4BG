//
// Created by Benjam on 13-04-21.
//

#include "Renderer3D.h"
#include "Shaders/Shader.h"
#include "Object/Object3D.h"
#include "Object/Cube.h"
#include "Camera/ICamera.h"
#include "Camera/MainCamera.h"

#define GLEW_STATIC
#include <GL/glew.h>


namespace Math4BG
{
    Renderer3D::Renderer3D(SDL_Window *window, unsigned int width, unsigned int height) :
            IRenderer(window, width, height),
            m_glContext(SDL_GL_CreateContext(window)),
            m_window(window)
    {
        //glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glEnable(GL_CULL_FACE);

        /*glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glCullFace(GL_BACK);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

        GlewInitAttempt();
        glViewport(0, 0, width, height);

    }

    Renderer3D::~Renderer3D()
    {
        SDL_GL_DeleteContext(m_glContext);
    }

    void Renderer3D::Draw(MainCamera *camera, IDrawable *drawable)
    {
        //--- TEST : TO DELETE ---//
        auto* object = (Object3D*) drawable;
        object->Bind(camera);
    }

    std::shared_ptr<Renderer3D> Renderer3D::Create(SDL_Window *window, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<Renderer3D>(static_cast<Renderer3D *>(new Renderer3D(window, width, height)));
    }

    void Renderer3D::Clear()
    {
        glClearColor(Col(m_background.r), Col(m_background.g), Col(m_background.b), Col(m_background.a));
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    float Renderer3D::Col(uint32_t color)
    {
        return ((float) color) / 0xFF;
    }

    void Renderer3D::GlewInitAttempt()
    {
        if(!glewInitialized)
        {
            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK)
                throw std::runtime_error("Failed to initialize GLEW.");

            /*printf("----------------------------------------------------------------\n");
            printf("Graphics Successfully Initialized\n");
            printf("OpenGL Info\n");
            printf("    Version: %s\n", glGetString(GL_VERSION));
            printf("     Vendor: %s\n", glGetString(GL_VENDOR));
            printf("   Renderer: %s\n", glGetString(GL_RENDERER));
            printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
            printf("----------------------------------------------------------------\n");*/

            glewInitialized = true;
        }
    }

    void Renderer3D::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
    {
        IRenderer::SetBackgroundColor(r, g, b);
        glClearColor(Col(m_background.r), Col(m_background.g), Col(m_background.b), Col(m_background.a));
    }

    void Renderer3D::SwapBuffers()
    {
        SDL_GL_SwapWindow(m_window);
    }
}
