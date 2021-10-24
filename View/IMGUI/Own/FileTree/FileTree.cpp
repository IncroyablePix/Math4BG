//
// Created by Benjam on 10/20/2021.
//

#include "FileTree.h"
#include "../../imgui.h"

namespace Math4BG
{
    FileTree::FileTree(const std::string &name) : m_name(name)
    {

    }

    FileTree::~FileTree() = default;

    void FileTree::Show()
    {
        ImGui::Text("Files!");
    }

    void FileTree::Begin()
    {
        ImGui::Begin(m_name.c_str());
    }

    void FileTree::End()
    {
        ImGui::End();
    }
}