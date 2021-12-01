//
// Created by Benjam on 12/1/2021.
//

#ifndef MATH4BG_TOPMENU_H
#define MATH4BG_TOPMENU_H


#include "../IGuiElement.h"
#include "../../../../Transformers/Project/ProjectManager.h"
#include "../../ImGuiFileBrowser.h"
#include <memory>

namespace Math4BG
{
    class TopMenu : public IGuiElement
    {
    public:
        TopMenu(std::shared_ptr<ProjectManager> packageManager, std::shared_ptr<IOutput> output);
        ~TopMenu();

        void SetProjectManager(std::shared_ptr<ProjectManager> projectManager);

        void Begin() override;
        void End() override;
        const std::string & GetName() override;
        void Show() override;

    private:
        bool m_opening;
        bool m_creating;
        std::shared_ptr<ProjectManager> m_packageManager;
        std::shared_ptr<IOutput> m_output;

        std::unique_ptr<imgui_addons::ImGuiFileBrowser> m_fileDialog;
        std::unique_ptr<imgui_addons::ImGuiFileBrowser> m_newProjectDialog;
    };
}

#endif //MATH4BG_TOPMENU_H
