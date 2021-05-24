//
// Created by Benjam on 11-04-21.
//

#include <stdexcept>
#include <iostream>
#include <functional>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include "Window.h"
#include "Renderer/2D/Renderer2D.h"
#include "Renderer/3D/Renderer3D.h"
#include "Renderer/3D/Camera/MainCamera.h"


namespace Math4BG
{
    Window::Window(const WindowInfo &info, WorldType worldType) :
            m_window(nullptr, SDL_DestroyWindow),
            m_title(info.title),
            m_renderer(nullptr)
    {
        InitSDL();


        m_window.reset(SDL_CreateWindow(info.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.width,
                                        info.height, FlagsFor(worldType)));

        m_renderer = CreateRenderer(m_window.get(), info.width, info.height, worldType);

        /*if(worldType == Flat)
            m_renderer = Renderer2D::Create(m_window.get(), info.width, info.height);*/

        if (!m_window)
            throw std::runtime_error("La fenêtre n'a pas pu être créée !");
    }

    Window::~Window()
    {
        //SDL_Quit();
    }

    void Window::UpdateWindowTitle()
    {
        std::ostringstream ss;
        ss << m_title << " (" << m_fps << "FPS - " << m_ups << "UPS)";
        SDL_SetWindowTitle(m_window.get(), ss.str().c_str());
    }


    void Window::SetFPS(unsigned int fps)
    {
        m_fps = fps;
    }

    void Window::SetUPS(unsigned int ups)
    {
        m_ups = ups;
        UpdateWindowTitle();
    }

    void Window::Draw(MainCamera* camera, IDrawable* drawable)
    {
        //m_renderer->Clear();
        if(drawable)
            m_renderer->Draw(camera, drawable);
    }

    void Window::Clear()
    {
        //m_renderer->Clear();
        m_renderer->Clear();
    }

    std::shared_ptr<Window> Window::Create(const WindowInfo &info, WorldType type)
    {
        return std::shared_ptr<Window>(static_cast<Window *>(new Window(info, type)));
    }

    std::shared_ptr<IRenderer>
    Window::CreateRenderer(SDL_Window *window, unsigned int width, unsigned int height, WorldType worldType)
    {
        switch (worldType)
        {
            case Flat:
                return std::shared_ptr<IRenderer>(Renderer2D::Create(window, width, height));
            case Relief:
                return std::shared_ptr<IRenderer>(Renderer3D::Create(window, width, height));
        }

        throw std::runtime_error("Invalid WorldType specified !");
    }

    uint32_t Window::FlagsFor(WorldType worldType)
    {
        uint32_t flag = SDL_WINDOW_SHOWN;

        if (worldType == Relief)
            flag = SDL_WINDOW_OPENGL;

        return flag;
    }

    void Window::InitSDL()
    {
        if(!sdlInitialized)
        {
            if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO))
                throw std::runtime_error(SDL_GetError());

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            /*SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

            SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
            SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
            SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );*/
            SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
            sdlInitialized = true;
        }
    }

    void Window::SwapBuffers()
    {
        m_renderer->SwapBuffers();
    }
}

