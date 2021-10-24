//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_EDITORVIEW_H
#define MATH4BG_EDITORVIEW_H

#include <string>
#include "../IGuiElement.h"
#include "../CodeEditor.h"
#include "../../../../Transformers/Contexts.h"

namespace Math4BG
{
    class EditorView : public IGuiElement
    {
    public:
        EditorView(const std::string& name);
        void Show() override;
        const std::string& GetName() override;
        void Begin() override;
        void End() override;

        void SetContexts(std::shared_ptr<Contexts> contexts);
        void SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor);

    private:
        std::shared_ptr<CodeEditor> m_codeEditor;
        std::shared_ptr<Contexts> m_contexts;
        std::string m_name;
    };
}

#endif //MATH4BG_EDITORVIEW_H
