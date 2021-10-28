//
// Created by Benjam on 12-04-21.
//

#include "Context.h"
#include "../View/IMGUI/imgui.h"

namespace Math4BG
{
    Context::Context(const WindowInfo &info) :
            //m_window(Window::Create(info, worldType)),
            m_title(info.title)
    {
        m_renderer = OG33Renderer::Create(info.width, info.height);
        m_world = std::make_shared<World>(info, m_renderer);//m_window->GetRenderer());
    }

    Context::~Context()
    {

    }

    void Context::Update(double lag)
    {
        /*m_mouse.Update();
        m_keys.Update();*/

        //m_window->Clear();
        m_world->Update(lag);//, m_mouse, m_keys);
    }

    void Context::SetUPS(int ups)
    {
        //m_window->SetUPS(ups);
    }

    void Context::SetFPS(int fps)
    {
        //m_window->SetFPS(fps);
    }

    void Context::Draw()
    {
        m_world->Draw(m_title);
    }
}
