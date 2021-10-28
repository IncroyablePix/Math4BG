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
#include "IMGUI/imgui_sdl.h"
#include "IMGUI/imgui.h"
#include "Renderer/OG33RendererSDL.h"
#include "Renderer/3D/Camera/MainCamera.h"


namespace Math4BG
{
    Window::Window(const WindowInfo &info) :
            IWindow(info),
            m_window(nullptr, SDL_DestroyWindow),
            m_sdlRenderer(nullptr, SDL_DestroyRenderer),
            m_renderer(nullptr)
    {
        InitSDL();

        m_window.reset(SDL_CreateWindow(info.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.width,
                                        info.height, FlagsFor()));
        m_sdlRenderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
        m_renderer = CreateRenderer(m_window.get(), info.width, info.height);

        if (!m_window)
            throw std::runtime_error("La fenêtre n'a pas pu être créée !");
    }

    Window::~Window()
    {
        /*ImGuiSDL::Deinitialize();
        ImGui::DestroyContext();*/
        //SDL_Quit();
    }

    void Window::UpdateWindowTitle()
    {
        std::ostringstream ss;
        ss << m_title << " (" << m_fps << "FPS - " << m_ups << "UPS)";
        SDL_SetWindowTitle(m_window.get(), ss.str().c_str());
    }

    void Window::MakeCurrentContext()
    {
        m_renderer->MakeContextCurrent(m_window.get());
    }

    void Window::Draw(MainCamera* camera, IDrawable* drawable)
    {
        //m_renderer->Clear();
        if(drawable)
            m_renderer->Draw(camera, drawable);
    }

    void Window::DrawGUI()
    {
        /*ImGui::NewFrame();
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
        SDL_RenderPresent(m_sdlRenderer.get());*/
    }

    void Window::Clear()
    {
        //m_renderer->Clear();
        m_renderer->Clear();
    }

    std::shared_ptr<Window> Window::Create(const WindowInfo &info, WorldType type)
    {
        return std::shared_ptr<Window>(static_cast<Window *>(new Window(info)));
    }

    std::shared_ptr<OG33RendererSDL>
    Window::CreateRenderer(SDL_Window *window, unsigned int width, unsigned int height)
    {
        /*switch (worldType)
        {
            case Flat:
                return std::shared_ptr<OG33RendererSDL>(Renderer2D::Create(window, width, height));
            case Relief:
                return std::shared_ptr<OG33RendererSDL>(Renderer3D::Create(window, width, height));
        }

        throw std::runtime_error("Invalid WorldType specified !");*/
        return OG33RendererSDL::Create(window, width, height);
    }

    uint32_t Window::FlagsFor()
    {
        uint32_t flag = SDL_WINDOW_SHOWN;

        //if (worldType == Relief)
            flag |= SDL_WINDOW_OPENGL;

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
        SDL_GL_SwapWindow(m_window.get());
        //m_renderer->SwapBuffers();
    }

    void Window::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;
    }
}

