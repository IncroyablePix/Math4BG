//
// Created by Benjam on 13-04-21.
//

#include "Renderer3D.h"
#include "Shaders/Shader.h"
#include "Object/Object3D.h"
#include <GL/glew.h>


namespace Math4BG
{
    Renderer3D::Renderer3D(SDL_Window *window, unsigned int width, unsigned int height) :
            IRenderer(window, width, height),
            m_glContext(SDL_GL_CreateContext(window)),
            m_window(window)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GlewInitAttempt();

        //--- TEST : TO REMOVE ---//

        shader = Shader::CreateShader(ParseShader("shaders/basic.shader"));
        shader->Bind();
        shader->SetUniform4f("vColor", 1.0f, 1.0f, 1.0f, 1.0f);

        IndexBufferContainer ibc{ (new unsigned int[36]
                                            {
                                                    0, 1, 2, // Face en face
                                                    2, 3, 0,

                                                    0, 1, 4, // Face du bas
                                                    1, 4, 5,

                                                    3, 4, 7, // Face gauche
                                                    0, 3, 4,

                                                    4, 5, 9, // Face arrière
                                                    6, 7, 4,

                                                    2, 3, 6, // Face du haut
                                                    3, 6, 7,

                                                    1, 2, 5, // Face droite
                                                    2, 5, 6
                                            }), 36 };
        m_object = std::make_unique<Object3D>(shader, ibc);

        m_object->Unbind();
    }

    Renderer3D::~Renderer3D()
    {
        SDL_GL_DeleteContext(m_glContext);
    }

    void Renderer3D::Draw(IDrawable *drawable)
    {
        //glViewport(0, 0, m_screen.width, m_screen.height);

        //--- TEST : TO DELETE ---//
        ((Object3D*) drawable)->Bind();
        m_object->Bind();
        //glColor4b(0xFF, 0xFF, 0xFF, 0xFF);
        //m_object->Bind();
    }

    std::shared_ptr<Renderer3D> Renderer3D::Create(SDL_Window *window, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<Renderer3D>(static_cast<Renderer3D *>(new Renderer3D(window, width, height)));
    }

    void Renderer3D::Clear()
    {
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
