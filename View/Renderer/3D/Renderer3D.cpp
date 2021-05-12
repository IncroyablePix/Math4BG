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
        shader->Unbind();

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


        //---

        /*unsigned int vertexBuffer, indexBuffer;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        float vertices[3 * 3] =
                {
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.0f, 0.5f, 0.0f
                };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
    }

    Renderer3D::~Renderer3D()
    {
        SDL_GL_DeleteContext(m_glContext);
    }

    void Renderer3D::Draw(IDrawable *drawable)
    {

        //shader->Bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);


        // On affiche le triangle

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        //--- TEST : TO DELETE ---//
        //((Object3D*) drawable)->Bind();
        //m_object->Bind();
        //glColor4b(0xFF, 0xFF, 0xFF, 0xFF);
        //m_object->Bind();
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

            printf("----------------------------------------------------------------\n");
            printf("Graphics Successfully Initialized\n");
            printf("OpenGL Info\n");
            printf("    Version: %s\n", glGetString(GL_VERSION));
            printf("     Vendor: %s\n", glGetString(GL_VENDOR));
            printf("   Renderer: %s\n", glGetString(GL_RENDERER));
            printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
            printf("----------------------------------------------------------------\n");

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
