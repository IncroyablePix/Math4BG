//
// Created by Benjam on 13-04-21.
//

#include "OG33RendererSDL.h"
#include <GL/glew.h>

namespace Math4BG
{
    OG33RendererSDL::OG33RendererSDL(SDL_Window *window, unsigned int width, unsigned int height) :
            m_screen(width, height),
            m_background{0x0, 0x0, 0x0, 0xFF},
            m_glContext(SDL_GL_CreateContext(window))
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glCullFace(GL_BACK);

        GlewInitAttempt();
        glViewport(0, 0, width, height);
    }

    OG33RendererSDL::~OG33RendererSDL()
    {
        SDL_GL_DeleteContext(m_glContext);
    }


    float OG33RendererSDL::Col(uint32_t color)
    {
        return ((float) color) / 0xFF;
    }

    void OG33RendererSDL::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
    {
        m_background.r = r;
        m_background.g = g;
        m_background.b = b;
        m_background.a = 1.0f;
        glClearColor(Col(m_background.r), Col(m_background.g), Col(m_background.b), Col(m_background.a));
    }

    void OG33RendererSDL::Clear()
    {
        glClearColor(Col(m_background.r), Col(m_background.g), Col(m_background.b), Col(m_background.a));
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OG33RendererSDL::GlewInitAttempt()
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

    void OG33RendererSDL::Draw(ICamera *camera, IDrawable *drawable)
    {
        drawable->Bind(*camera);
    }

    std::shared_ptr<OG33RendererSDL> OG33RendererSDL::Create(SDL_Window *window, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<OG33RendererSDL>(static_cast<OG33RendererSDL *>(new OG33RendererSDL(window, width, height)));
    }
}