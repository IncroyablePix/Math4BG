//
// Created by Benjam on 10/20/2021.
//

#include "EditorView.h"

namespace Math4BG
{

    EditorView::EditorView(const std::string &name) : m_name(name)
    {

    }

    void EditorView::Begin()
    {
        ImGui::Begin(m_name.c_str(), nullptr, ImGuiWindowFlags_MenuBar);
    }

    void EditorView::End()
    {
        ImGui::End();
    }

    void EditorView::Show()
    {
        ImGui::BeginTabBar("Windows");
        if(ImGui::BeginTabItem("Code"))
        {
            if(m_codeEditor)
                m_codeEditor->Show();

            ImGui::EndTabItem();
        }
        
        m_contexts->SetWindowFocused(ImGui::IsWindowFocused());

        if(m_contexts)
            m_contexts->DrawContexts();

        ImGui::EndTabBar();
    }

    const std::string &EditorView::GetName()
    {
        return m_name;
    }

    void EditorView::SetContexts(std::shared_ptr<Contexts> contexts)
    {
        m_contexts = std::move(contexts);
    }

    void EditorView::SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor)
    {
        m_codeEditor = std::move(codeEditor);
    }
}