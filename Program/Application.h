//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_APPLICATION_H
#define ARCPOSITION_APPLICATION_H


#include "../View/Window.h"
#include "../Transformers/Interpreter/LuaInterpreter.h"
#include "Config/Config.h"
#include "../Transformers/Context.h"
#include "../Transformers/Contexts.h"
#include "../Output/IOutput.h"
#include "../View/Windowing/MainWindow.h"
#include "../View/IMGUI/Own/CodeEditor.h"
#include "../Transformers/Project/ProjectManager.h"

namespace Math4BG
{
    class Application
    {
    public:
        Application(const WindowInfo &info, std::shared_ptr<Contexts> contexts, const Config &config, std::shared_ptr<IOutput> output);
        ~Application();
        void Start();

    private:

        std::shared_ptr<ProjectManager> m_projectManager;
        MainWindow m_window;

        std::shared_ptr<Contexts> m_contexts;
        std::shared_ptr<IOutput> m_output;
        std::shared_ptr<CodeEditor> m_codeEditor;
        unsigned long long m_start;
        unsigned long long m_last;
        bool m_running;
        bool m_fpsLimiter;
        int m_refreshRate;

        void Update(double lag);

        void Run();

        static std::unique_ptr<ILanInterpreter> CreateInterpreter(const std::string& name, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
    };
}

#endif //ARCPOSITION_APPLICATION_H
