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

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        ImGui::Begin(m_title.c_str(), nullptr, windowFlags);

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            auto wSize = ImGui::GetWindowSize();
            ImGuiID dockspaceId = ImGui::GetID(m_title.c_str());
            ImGui::DockSpace(dockspaceId, ImVec2(), dockspaceFlags);
            std::cout << wSize.x << " " << wSize.y << std::endl;

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

        ImGui::End();

        for(const auto& [slot, element] : m_elements)
        {
            element->Show();
        }
    }

    void DockSpace::ShowElements(ImGuiID dockspaceId)
    {
        for(const auto& [slot, element] : m_elements)
        {
            if(slot != DOCK_CENTER)
            {
                auto dock = ImGui::DockBuilderSplitNode(dockspaceId, slot, 0.2f, nullptr, &dockspaceId);
                ImGui::DockBuilderDockWindow(element->GetName().c_str(), dock);
            }
        }
    }
}