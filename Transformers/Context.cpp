//
// Created by Benjam on 12-04-21.
//

#include "Context.h"
#include "../View/IMGUI/imgui.h"
#include "World/AbstractWorld.h"
#include "World/ConcreteWorld.h"

namespace Math4BG
{
    Context::Context(const WindowInfo &info, bool abstract) :
            //m_window(Window::Create(info, worldType)),
            m_title(info.title)
    {
        m_renderer = OG33Renderer::Create(info.width, info.height);
        if(abstract)
            m_world = std::make_shared<AbstractWorld>(info, m_renderer);
        else
            m_world = std::make_shared<ConcreteWorld>(info, m_renderer);//m_window->GetRenderer());
    }

    Context::~Context()
    = default;

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
