//
// Created by Benjam on 10/28/2021.
//

#ifndef MATH4BG_PROJECTMANAGER_H
#define MATH4BG_PROJECTMANAGER_H

#include <memory>
#include "../Interpreter/ILanInterpreter.h"
#include "../../View/IMGUI/Own/CodeEditor.h"

namespace Math4BG
{
    class ProjectManager : public std::enable_shared_from_this<ProjectManager>
    {
    public:
        ProjectManager(const std::string &path, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        void SetPath(const std::string &path);
        void Run();
        void Reload();
        void Update(double deltaTime);
        void SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor);

    private:
        std::string m_path;
        std::shared_ptr<IOutput> m_output;
        std::shared_ptr<Contexts> m_contexts;
        std::unique_ptr<ILanInterpreter> m_interpreter;
        std::shared_ptr<CodeEditor> m_codeEditor;

        bool m_runningProject { false };

        static std::unique_ptr<ILanInterpreter> CreateInterpreter(const std::string& name, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
    };
}

#endif //MATH4BG_PROJECTMANAGER_H
