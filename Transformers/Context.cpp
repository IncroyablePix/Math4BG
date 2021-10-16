//
// Created by Benjam on 12-04-21.
//

#include "Context.h"
#include "../View/IMGUI/imgui.h"

namespace Math4BG
{
    Context::Context(const WindowInfo &info, WorldType worldType) :
            //m_window(Window::Create(info, worldType)),
            m_title(info.title)
    {
        m_renderer = OG33Renderer::Create(info.width, info.height);
        m_world = std::make_shared<World>(info, worldType, m_renderer);//m_window->GetRenderer());
    }

    Context::~Context()
    {

    }

    void Context::Update(double lag)
    {
        m_mouse.Update();
        m_keys.Update();

        //m_window->Clear();
        m_world->Update(lag, m_mouse, m_keys);
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
        //m_window->Clear();
        //m_window->MakeCurrentContext();

        /*m_world->Draw();
        if(ImGui::BeginTabItem(GetTitle().c_str()))
        {
            ImVec2 wsize = ImGui::GetWindowSize();
            //m_world->Resize(wsize.x, wsize.y);
            //glViewport(0, 0, 1280, 720);
            ImGui::GetWindowDrawList()->AddImage(m_world->GetFboTexture().get(), wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndTabItem();
        }*/
        //m_window->SwapBuffers();
        /*glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glCullFace(GL_BACK);*/

        m_world->Draw(m_title);
        /*ImGui::Begin("Game rendering");
        // Get the current cursor position (where your window is)
        ImVec2 pos = ImGui::GetCursorScreenPos();

        // A boolean to allow me to stop the game rendering

        //glViewport(0, 0, W, H);
        //m_world->Resize(W + 10, H + 10);
        // Render the scene into an FBO
        // Restore previous viewport
        //glViewport(0, 0, m_renderer->Width(), m_renderer->Height());

        // Get the texture associated to the FBO
        auto tex = (m_world->GetFboId());

        // Ask ImGui to draw it as an image:
        // Under OpenGL the ImGUI image type is GLuint
        // So make sure to use "(void *)tex" but not "&tex"
        ImGui::GetWindowDrawList()->AddImage(
                (void *)(tex), {0, 0},
                {(float) m_renderer->Width(), (float) m_renderer->Height()},
                ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();*/
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
