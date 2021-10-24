//
// Created by Benjam on 10/20/2021.
//

#include "GuiConsole.h"
#include "../imgui.h"

namespace Math4BG
{
    void GuiConsole::Show()
    {
        //ImGui::Begin(m_name.c_str());

        /*if(m_output)
            m_output->PrintMessages();*/

        //ImGui::End();
        if(m_output)
            m_output->PrintMessages();

        if(m_autoScroll)
            ImGui::SetScrollHereY(1.0f);

    }

    GuiConsole::GuiConsole(const std::string &name, std::shared_ptr<IOutput> output) : m_output(std::move(output)), m_name(name)
    {

    }

    void GuiConsole::Begin()
    {
        ImGui::Begin(m_name.c_str());
    }

    void GuiConsole::End()
    {
        ImGui::End();
    }
}