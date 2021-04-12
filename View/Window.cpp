//
// Created by Benjam on 11-04-21.
//

#include <stdexcept>
#include <iostream>
#include <functional>
#include <sstream>
#include "Window.h"

Window::Window(WindowInfo *info) :
        m_window(nullptr, SDL_DestroyWindow),
        m_title(info->title),
        m_renderer(nullptr)
{
    if(SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(SDL_GetError());

    m_window.reset(SDL_CreateWindow(info->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info->width, info->height, SDL_WINDOW_SHOWN));

    m_renderer = Renderer::Create(m_window.get(), info->width, info->height);

    if(!m_window)
        throw std::runtime_error("La fenêtre n'a pas pu être créée !");
}

Window::~Window()
{
    SDL_Quit();
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

void Window::Draw()
{
    m_renderer->Draw();
}

std::shared_ptr<Window> Window::Create(WindowInfo *info)
{
    return std::shared_ptr<Window>(static_cast<Window*>(new Window(info)));
}
