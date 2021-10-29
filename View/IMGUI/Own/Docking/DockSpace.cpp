//
// Created by Benjam on 10/20/2021.
//

#include <iostream>
#include "DockSpace.h"
#include "../../imgui_internal.h"

namespace Math4BG
{
    DockSpace::DockSpace(const std::string &title, ImGuiID dockspaceId) : m_title(title), m_dockspaceId(dockspaceId)
    {

    }

    DockSpace::~DockSpace()
    {

    }

    void DockSpace::AddElement(std::shared_ptr<IGuiElement> element, DockSlot slot)
    {
        m_elements[slot] = std::move(element);
    }

    void DockSpace::Show()
    {
        ImGuiIO& io = ImGui::GetIO();
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        Begin();

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            auto wSize = ImGui::GetWindowSize();
            ImGuiID dockspaceId = ImGui::GetID(m_title.c_str());
            ImGui::DockSpace(dockspaceId, ImVec2(), dockspaceFlags);

            if (m_firstTime)
            {
                m_firstTime = false;

                ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_CentralNode);
                ImGui::DockBuilderSetNodeSize(dockspaceId, wSize);

                ShowElements(dockspaceId);

                ImGui::DockBuilderFinish(dockspaceId);
            }
        }
        End();
    }

    void DockSpace::ShowElements(ImGuiID dockspaceId)
    {
        /*if(m_elements.find(DOCK_CENTER) != m_elements.end())
        {
            auto element = m_elements[DOCK_CENTER];
            auto dock = ImGui::GetID(element->GetName().c_str());
            //ImGui::DockBuilderDockWindow(element->GetName().c_str(), dock);
            ImGui::DockBuilderAddNode(dock, ImGuiDockNodeFlags_PassthruCentralNode);
        }*/

        for(const auto& [slot, element] : m_elements)
        {
            if(slot != DOCK_CENTER)
            {
                auto dock = ImGui::DockBuilderSplitNode(dockspaceId, slot, element->GetDockSize(), nullptr, &dockspaceId);
                ImGui::DockBuilderDockWindow(element->GetName().c_str(), dock);
            }
        }
    }

    void DockSpace::Begin()
    {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin(m_title.c_str(), nullptr, windowFlags);
    }

    void DockSpace::End()
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
}