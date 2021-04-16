//
// Created by Benjam on 12-04-21.
//

#include "Context.h"

namespace Math4BG
{
    Context::Context(const WindowInfo &info, WorldType worldType) :
            m_window(Window::Create(info, worldType))
    {
        m_world = std::make_shared<World>(worldType, m_window->GetRenderer());
    }

    Context::~Context()
    {

    }

    void Context::Update()
    {
        m_window->Clear();
        m_world->Update();
    }

    void Context::SetUPS(int ups)
    {
        m_window->SetUPS(ups);
    }

    void Context::SetFPS(int fps)
    {
        m_window->SetFPS(fps);
    }

    void Context::Draw()
    {
        //m_window->Clear();
        m_world->Draw(*m_window);
        m_window->SwapBuffers();
    }
}
