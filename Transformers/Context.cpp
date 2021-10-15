//
// Created by Benjam on 12-04-21.
//

#include "Context.h"

namespace Math4BG
{
    Context::Context(const WindowInfo &info, WorldType worldType) :
            m_window(Window::Create(info, worldType))
    {
        m_world = std::make_shared<World>(info, worldType, m_window->GetRenderer());
    }

    Context::~Context()
    {

    }

    void Context::Update(double lag)
    {
        m_mouse.Update();
        m_keys.Update();

        m_window->Clear();
        m_world->Update(lag, m_mouse, m_keys);
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
        m_window->MakeCurrentContext();
        m_world->Draw(*m_window);
        m_window->SwapBuffers();
    }

    void Context::KeySet(KeyButton button, bool state)
    {
        m_keys.KeySet(button, state);
    }

    void Context::MouseSet(MouseButton button, bool state)
    {
        m_mouse.MouseSet(button, state);
    }

    void Context::MousePos(const glm::vec2 &position)
    {
        m_mouse.MousePos(position);
    }
}
