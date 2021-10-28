//
// Created by Benjam on 10/28/2021.
//

#include "ProjectManager.h"
#include "../Interpreter/LuaInterpreter.h"
#include "../../Utils/FileSplit.h"

namespace Math4BG
{
    ProjectManager::ProjectManager(const std::string &path, std::shared_ptr<Contexts> contexts,
                                   std::shared_ptr<IOutput> output) :
                                   m_path(path),
                                   m_contexts(std::move(contexts)),
                                   m_output(std::move(output))
    {

    }

    void ProjectManager::SetPath(const std::string &path)
    {
        m_path = path;
    }

    void ProjectManager::Run()
    {
        m_contexts->Clear();

        if(m_codeEditor)
            m_codeEditor->SetFile(m_path);

        FileSplit fileSplit(m_path);
        m_interpreter = std::move(CreateInterpreter(fileSplit.fileExtension, m_contexts, m_output));

        m_interpreter->ExecuteFile(m_path);

        if (!m_interpreter->CheckValidity())
        {
            *m_output << "Invalid Script: ";
            throw std::runtime_error(
                    "Invalid Lua script :\nMust contain the following functions : OnInit, OnUpdate(number), OnWindowClosed(windowId)");
        }
        else
        {
            m_interpreter->CallOnInitFunction();
        }
    }

    std::unique_ptr<ILanInterpreter> ProjectManager::CreateInterpreter(const std::string &name, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output)
    {
        if(name == "lua")
            return std::move(LuaInterpreter::Create(std::move(contexts), std::move(output)));
        /*else if(name == "js")
            return std::shared_ptr<ILanInterpreter>(JavascriptInterpreter::Create(contexts, output));*/

        throw std::runtime_error("Invalid Interpreter specified!");
    }

    void ProjectManager::Update(double deltaTime)
    {
        m_interpreter->CallUpdateFunction(deltaTime);
    }

    void ProjectManager::SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor)
    {
        m_codeEditor = std::move(codeEditor);
    }
}