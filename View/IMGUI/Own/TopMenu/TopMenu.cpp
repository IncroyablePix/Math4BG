//
// Created by Benjam on 12/1/2021.
//

#include "TopMenu.h"
#include "../../ImGuiFileBrowser.h"

namespace Math4BG
{

    TopMenu::TopMenu(std::shared_ptr<ProjectManager> packageManager, std::shared_ptr<IOutput> output) :
        m_packageManager(std::move(packageManager)),
        m_fileDialog(std::make_unique<imgui_addons::ImGuiFileBrowser>()),
        m_newProjectDialog(std::make_unique<imgui_addons::ImGuiFileBrowser>()),
        m_output(std::move(output))
    {

    }

    TopMenu::~TopMenu()
    {

    }

    void TopMenu::Begin()
    {

    }

    void TopMenu::End()
    {

    }

    const std::string &TopMenu::GetName()
    {
        return "";
    }

    void TopMenu::Show()
    {
        m_creating = false;
        m_opening = false;
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("New project", nullptr))
                {
                    m_creating = true;
                }
                if(ImGui::MenuItem("Open...", nullptr))
                {
                    m_opening = true;
                }
                if(ImGui::MenuItem("Reload", nullptr))
                {
                    m_packageManager->Reload();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if(m_creating)
        {
            ImGui::OpenPopup("New Project");
        }

        if(m_newProjectDialog->showFileDialog("New Project", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310)))
        {
            std::stringstream ss; ss << "Creating new project: " << m_newProjectDialog->selected_fn << " in " << m_newProjectDialog->selected_path;
            *m_output << ss.str();

            if(m_packageManager)
            {
                m_packageManager->Create(m_newProjectDialog->selected_fn, m_newProjectDialog->selected_path);
            }
        }

        if(m_opening)
        {
            ImGui::OpenPopup("Open File");
        }

        if(m_fileDialog->showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".m4bg"))
        {
            std::stringstream ss; ss << "Opening " << m_fileDialog->selected_fn;
            *m_output << ss.str();
            /*std::cout << m_fileDialog->selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << m_fileDialog->selected_path << std::endl;    // The absolute path to the selected file*/

            if(m_packageManager)
            {
                m_packageManager->SetPath(m_fileDialog->selected_path);
                m_packageManager->Run();
            }
        }
    }

    void TopMenu::SetProjectManager(std::shared_ptr<ProjectManager> projectManager)
    {
        m_packageManager = std::move(projectManager);
    }
}