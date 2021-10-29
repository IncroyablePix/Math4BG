//
// Created by Benjam on 10/28/2021.
//

#include "ProjectManager.h"
#include "../Interpreter/LuaInterpreter.h"
#include "../../Utils/FileSplit.h"
#include "../Interpreter/CodeException.h"

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

    void ProjectManager::Reload()
    {
        Run();
    }

    void ProjectManager::Run()
    {
        m_runningProject = false;
        m_contexts->Clear();

        if(m_codeEditor)
            m_codeEditor->SetFile(m_path);

        FileSplit fileSplit(m_path);
        m_interpreter = std::move(CreateInterpreter(fileSplit.fileExtension, m_contexts, m_output));

        try { m_interpreter->ExecuteFile(m_path); }
        catch(const CodeException &e) { *m_output << e.what(); }

        m_runningProject = true;
        try { m_interpreter->CallOnInitFunction(); }
        catch(const CodeException &e) { *m_output << e.what(); }
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
        if(m_runningProject)
        {
            try { m_interpreter->CallUpdateFunction(deltaTime); }
            catch(const CodeException &e) { *m_output << e.what(); }
        }
    }

    void ProjectManager::SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor)
    {
        m_codeEditor = std::move(codeEditor);
    }
}