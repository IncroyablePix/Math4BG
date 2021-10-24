//
// Created by Benjam on 10/19/2021.
//

#include <fstream>
#include "CodeEditor.h"
#include "../../../Utils/FileSplit.h"
#include "../../Error.h"

namespace Math4BG
{
    CodeEditor::CodeEditor(const std::string &path, std::function<void(const std::string &path)> reloadCallback,
                           const std::string &name) :
        m_path(path),
        m_lanDef(GetLanguageDefinition(path)),
        m_name(name)
    {
        std::ifstream fileStream(path);
        if(fileStream.good())
        {
            std::string code((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            m_editor.SetText(code);
        }

        m_editor.SetLanguageDefinition(m_lanDef);
    }

    CodeEditor::~CodeEditor()
    {

    }

    void CodeEditor::ShowMenuBar()
    {
        if(ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save", "Ctrl-S"))
                {
                    Save();
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl-Z", nullptr, !m_readOnly && m_editor.CanUndo()))
                    m_editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !m_readOnly && m_editor.CanRedo()))
                    m_editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, m_editor.HasSelection()))
                    m_editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !m_readOnly && m_editor.HasSelection()))
                    m_editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, !m_readOnly && m_editor.HasSelection()))
                    m_editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !m_readOnly && ImGui::GetClipboardText() != nullptr))
                    m_editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    m_editor.SetSelection(TextEditor::Coordinates(),
                                          TextEditor::Coordinates(m_editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }

    void CodeEditor::Show()
    {
        ShowMenuBar();
        auto cursor = m_editor.GetCursorPosition();

        ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cursor.mLine + 1, cursor.mColumn + 1, m_editor.GetTotalLines(),
                    m_editor.IsOverwrite() ? "Ovr" : "Ins",
                    m_editor.CanUndo() ? "*" : " ",
                    m_editor.GetLanguageDefinition().mName.c_str(), m_path.c_str());

        m_editor.Render(m_name.c_str());
    }

    TextEditor::LanguageDefinition CodeEditor::GetLanguageDefinition(const std::string &path)
    {
        FileSplit fileSplit { path };
        if(fileSplit.fileExtension == "lua")
        {
            return TextEditor::LanguageDefinition::Lua();
        }

        return TextEditor::LanguageDefinition::C();
    }

    bool CodeEditor::Save()
    {
        std::ofstream fileStream(m_path);
        if(fileStream.good())
        {
            std::string code = m_editor.GetText();
            fileStream << code;
            Beep();
            return true;
        }
        else
        {
            return false;
        }
    }

    void CodeEditor::Begin()
    {

    }

    void CodeEditor::End()
    {

    }
}