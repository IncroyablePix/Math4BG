//
// Created by Benjam on 10/19/2021.
//

#ifndef MATH4BG_CODEEDITOR_H
#define MATH4BG_CODEEDITOR_H

#include <memory>
#include "../TextEditor.h"
#include "IGuiElement.h"

namespace Math4BG
{
    class CodeEditor : public std::enable_shared_from_this<CodeEditor>, public IGuiElement
    {
    public:
        CodeEditor(const std::string &path, const std::string &name);
        ~CodeEditor();
        void ShowMenuBar();
        void Show() override;
        void Begin() override;
        void End() override;
        bool Save();
        inline const std::string & GetName() override { return m_name; };
        void SetFile(const std::string &path);

    private:
        std::string m_name;
        std::string m_path;
        bool m_readOnly;
        TextEditor m_editor;
        TextEditor::LanguageDefinition m_lanDef;

        static TextEditor::LanguageDefinition GetLanguageDefinition(const std::string &path);
    };


}

#endif //MATH4BG_CODEEDITOR_H
