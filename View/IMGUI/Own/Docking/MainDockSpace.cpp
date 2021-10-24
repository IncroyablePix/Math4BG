//
// Created by Benjam on 10/20/2021.
//

#include "MainDockSpace.h"
#include "../../imgui.h"
#include "../../imgui_internal.h"

namespace Math4BG
{

    MainDockSpace::MainDockSpace(const std::string &title, ImGuiID dockspaceId) : DockSpace(title, dockspaceId)
    {

    }

    void MainDockSpace::Show()
    {
        ImGuiIO& io = ImGui::GetIO();
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        Begin();

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            ImGuiID dockspaceId = ImGui::GetID(m_title.c_str());
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

            if (m_firstTime)
            {
                m_firstTime = false;

                ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

                ShowElements(dockspaceId);

                ImGui::DockBuilderFinish(dockspaceId);
            }


            if(m_elements.find(DOCK_CENTER) != m_elements.end())
            {
                auto element = m_elements[DOCK_CENTER];
                element->Begin();
                element->Show();
                element->End();
                //ImGui::DockBuilderDockWindow(element->GetName().c_str(), dock);
                //ImGui::DockBuilderAddNode(dock, ImGuiDockNodeFlags_PassthruCentralNode);
            }
        }

        End();
    }

    void MainDockSpace::Begin()
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        // Central dockspace should take up all space
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;
        ImGui::Begin(m_title.c_str(), nullptr, windowFlags);
    }

    void MainDockSpace::End()
    {
        ImGui::End();

        for(const auto& [slot, element] : m_elements)
        {
            if(slot != DOCK_CENTER)
            {
                element->Begin();
                element->Show();
                element->End();
            }
        }
    }

    MainDockSpace::~MainDockSpace()
    = default;
}