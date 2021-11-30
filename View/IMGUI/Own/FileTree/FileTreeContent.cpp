//
// Created by Benjam on 11/30/2021.
//

#include "FileTreeContent.h"
#include "../../imgui.h"

namespace Math4BG
{
    void FileTreeContent::Show()
    {
        if (m_projectPackage)
        {
            if (m_projectPackage->fileStructure.Empty())
            {
                ImGui::Text("No files.");
            }
            else
            {
                if (ImGui::TreeNode(m_projectPackage->name.c_str()))
                {
                    ShowDirectory(m_projectPackage->fileStructure);
                    ImGui::TreePop();
                }
            }
        }
        else
        {
            ImGui::Text("No project opened.");
        }
    }

    void FileTreeContent::ShowDirectory(const FileStructure &fileStructure)
    {
        ImGui::Indent();
        for(const auto& [dir, content] : fileStructure.directories)
        {
            if(ImGui::TreeNode(dir.c_str()))
            {
                ShowDirectory(*content);
                ImGui::TreePop();
            }
        }

        for(const auto& file : fileStructure.files)
        {
            ImGui::Text("%s", file.c_str());
        }

        ImGui::Unindent();
    }

    void FileTreeContent::Begin()
    {

    }

    void FileTreeContent::End()
    {

    }

    const std::string &FileTreeContent::GetName()
    {
        return " ";
    }
}