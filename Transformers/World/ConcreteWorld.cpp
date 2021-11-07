//
// Created by Benjam on 11/6/2021.
//

#include "ConcreteWorld.h"

#include <utility>
#include "../../View/IMGUI/imgui.h"

namespace Math4BG
{
    ConcreteWorld::ConcreteWorld(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer) :
    IWorld(info,std::move(renderer))
    {

    }

    void ConcreteWorld::Draw(const std::string &title)
    {
        m_tabActive = false;
        if(ImGui::BeginTabItem(title.c_str()))
        {
            m_tabActive = true;

            ImGui::BeginChild("GameRender");

            // Get the size of the child (i.e. the whole draw size of the windows).
            ImVec2 windowSize = ImGui::GetWindowSize();
            auto pos = ImGui::GetCursorScreenPos();
            //m_fbo.SetSize(windowSize.x, windowSize.y);
            m_camera->SetViewportSize(windowSize.x, windowSize.y);
            DrawWorld();
            // Because I use the texture from OpenGL, I need to invert the V from the UV.

            //auto fboId = (ImTextureID) m_fbo.GetId();
            auto fboId = (void *) (m_fbo.GetTexture()->GetId());
            //ImGui::Image(fboId, windowSize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::GetWindowDrawList()->AddImage(fboId, ImVec2(pos), ImVec2(pos.x + windowSize.x, pos.y + windowSize.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        m_canvas.Bind(*m_ppShader, *m_fbo.GetTexture()); // Drawing frame buffer over canvas
    }

    void ConcreteWorld::HandleMouseInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        if(m_tabActive)//if(m_windowActive)// && m_tabActive)
        {
            m_mouse.MouseSet(LMB, ImGui::IsMouseDown(ImGuiMouseButton_Left));
            m_mouse.MouseSet(RMB, ImGui::IsMouseDown(ImGuiMouseButton_Right));
            m_mouse.MouseSet(MMB, ImGui::IsMouseDown(ImGuiMouseButton_Middle));
            //m_mouse.MouseSet(MWU, ImGui::IsMouseClicked(ImGuiMouseWheel));
            //m_mouse.MouseSet(MWD, ImGui::IsMouseClicked(4));

            m_mouse.MousePos({ImGui::GetMousePos().x, ImGui::GetMousePos().y});
        }
    }

    void ConcreteWorld::HandleKeyboardInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        if(m_tabActive)//if(m_windowActive)// && m_tabActive)
        {
            m_keys.KeySet(Z, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow)));
            m_keys.KeySet(S, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow)));
            m_keys.KeySet(Q, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)));
            m_keys.KeySet(D, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow)));
            m_keys.KeySet(PgUp, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageUp)));
            m_keys.KeySet(PgDn, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageDown)));
            //m_keys.KeySet(S, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_S)));
            //m_keys.KeySet(Q, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_A)));
            //m_keys.KeySet(D, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_)));
        }
    }

    void ConcreteWorld::Update(double lag)
    {
        HandleMouseInputs();
        HandleKeyboardInputs();
        m_camera->Update(m_mouse, m_keys, lag);

        IWorld::Update(lag);
    }
}