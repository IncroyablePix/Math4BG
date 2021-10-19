//
// Created by Benjam on 10/19/2021.
//

#ifndef MATH4BG_CODEEDITOR_H
#define MATH4BG_CODEEDITOR_H

#include <memory>
#include "../TextEditor.h"

namespace Math4BG
{
    class CodeEditor : public std::enable_shared_from_this<CodeEditor>
    {
    public:
        CodeEditor(const std::string &path, std::function<void(const std::string& path)> reloadCallback);
        ~CodeEditor();
        void ShowMenuBar();
        void Show();
        bool Save();

    private:
        std::string m_path;
        bool m_readOnly;
        TextEditor m_editor;
        TextEditor::LanguageDefinition m_lanDef;

        static TextEditor::LanguageDefinition GetLanguageDefinition(const std::string &path);
    };


}

#endif //MATH4BG_CODEEDITOR_H
