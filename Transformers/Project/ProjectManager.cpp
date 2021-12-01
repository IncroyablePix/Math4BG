//
// Created by Benjam on 10/28/2021.
//

#include <fstream>
#include <utility>
#include "ProjectManager.h"
#include "../Interpreter/LuaInterpreter.h"
#include "../Interpreter/JSInterpreter.h"
#include "../../Utils/FileSplit.h"
#include "../Interpreter/CodeException.h"
#include "../../IO/DirFile/FilesystemUtils.h"
#include "ProjectSaverLoader.h"
#include "../../IO/IOException.h"

namespace Math4BG
{
    ProjectManager::ProjectManager(std::string path,
                                   std::shared_ptr<Config> config,
                                   std::shared_ptr<Contexts> contexts,
                                   std::shared_ptr<IOutput> output) :
                                   m_path(std::move(path)),
                                   m_contexts(std::move(contexts)),
                                   m_output(std::move(output)),
                                   m_config(std::move(config))
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
        if(!m_path.empty())
        {
            try
            {
                m_project = std::move(LoadFromFile(m_path));

                m_config->projectPackage = m_path;
                SaveConfig(CONFIG_PATH, m_config);

                m_runningProject = false;
                m_contexts->Clear();

                if (m_codeEditor)
                    m_codeEditor->SetFile(m_project->mainScript);

                if(m_fileTreeContent)
                    m_fileTreeContent->SetProjectPackage(m_project);

                FileSplit fileSplit(m_path);// fileSplit.fileExtension
                m_contexts->SetRootPath(fileSplit.filePath);

                m_interpreter = std::move(CreateInterpreter(m_project->language, m_contexts, m_output));

                try { m_interpreter->ExecuteFile(m_project->mainScript); }
                catch (const CodeException &e) { *m_output << e.what(); }

                m_runningProject = true;
                try { m_interpreter->CallOnInitFunction(); }
                catch (const CodeException &e) { *m_output << e.what(); }
            }
            catch(const IOException e)
            {
                m_path = "";
                *m_output << "Could not load project.";
            }
        }
    }

    void ProjectManager::Create(const std::string &projectName, const std::string &path)
    {
        // Directory creation
        std::stringstream mainFile;
        std::string packageFile;
        std::stringstream ss; ss << path.c_str();
        CreateFileDirectories(ss.str());

        // Scripts
        {
            std::stringstream ssScripts;
            ssScripts << ss.str() << "/scripts";
            CreateFileDirectories(ssScripts.str());

            {
                mainFile << ssScripts.str() << "/main.lua";

                std::ofstream mainScript(mainFile.str());
                if(mainScript.good())
                    mainScript << std::endl;
            }
        }

        // Shaders
        {
            std::stringstream ssScripts;
            ssScripts << ss.str() << "/shaders";
            CreateFileDirectories(ssScripts.str());
        }

        // Sounds
        {
            std::stringstream ssScripts;
            ssScripts << ss.str() << "/sounds";
            CreateFileDirectories(ssScripts.str());
        }

        // Models
        {
            std::stringstream ssScripts;
            ssScripts << ss.str() << "/models";
            CreateFileDirectories(ssScripts.str());
        }

        // Textures
        {
            std::stringstream ssScripts;
            ssScripts << ss.str() << "/textures";
            CreateFileDirectories(ssScripts.str());
        }

        auto projectPackage = ProjectPackage::EmptyProject(projectName, path, LANGUAGE_LUA);
        // Config file creation
        {
            std::stringstream ssPackage(ss.str());
            ssPackage << ss.str() << "/package.m4bg";
            projectPackage->mainScript = packageFile = mainFile.str();

            SaveToFile(ssPackage.str(), projectPackage);
        }

        //---

        SetPath(packageFile);
        Run();
    }

    std::unique_ptr<ILanInterpreter> ProjectManager::CreateInterpreter(const std::string &name, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output)
    {
        if(name == LANGUAGE_LUA)
            return std::move(LuaInterpreter::Create(std::move(contexts), std::move(output)));
        else if(name == LANGUAGE_JS)
            return std::move(JSInterpreter::Create(std::move(contexts), std::move(output)));

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

    void ProjectManager::SetFileTreeContent(std::shared_ptr<FileTreeContent> fileTreeContent)
    {
        m_fileTreeContent = std::move(fileTreeContent);

        if(m_project)
            m_fileTreeContent->SetProjectPackage(m_project);
    }
}