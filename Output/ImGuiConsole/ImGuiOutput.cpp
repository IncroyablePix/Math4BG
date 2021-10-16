//
// Created by Benjam on 10/16/2021.
//

#include "ImGuiOutput.h"
#include "../../View/IMGUI/imgui.h"

namespace Math4BG
{

    ImGuiOutput::ImGuiOutput() : IOutput()
    {

    }

    std::shared_ptr<ImGuiOutput> ImGuiOutput::Create()
    {
        return std::make_shared<ImGuiOutput>();
    }

    void ImGuiOutput::PrintMessages()
    {
        for(size_t i = 0, j = m_messages.count(); i < j; i ++)
        {
            ImGui::Text("%s", m_messages[i].c_str());
        }
    }
}