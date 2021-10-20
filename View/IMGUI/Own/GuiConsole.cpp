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
        ImGui::Begin(m_name.c_str());
        if(m_output)
            m_output->PrintMessages();
        ImGui::End();
    }

    GuiConsole::GuiConsole(const std::string &name, std::shared_ptr<IOutput> output) : m_output(std::move(output)), m_name(name)
    {

    }
}