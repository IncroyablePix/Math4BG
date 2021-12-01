//
// Created by Benjam on 11-04-21.
//

#include <iostream>
#include <memory>
#include <utility>
#include "Application.h"
#include "../Input/MouseInput.h"
#include "../Input/KeyInput.h"
#include "../IO/OBJLoader.h"
#include "../View/IMGUI/imgui.h"
#include "../View/IMGUI/imgui_impl_sdl.h"
#include "../View/IMGUI/imgui_impl_opengl3.h"
#include "../Transformers/Interpreter/CodeException.h"

namespace Math4BG
{
    Application::Application(const WindowInfo &info, std::shared_ptr<Contexts> contexts, std::shared_ptr<Config> config, std::shared_ptr<IOutput> output) :
        m_config(std::move(config)),
        m_fpsLimiter(m_config->fpsLimiter),
        m_window(info, output),
        m_contexts(std::move(contexts)),
        m_output(std::move(output)),
        m_projectManager(std::make_shared<ProjectManager>(config->projectPackage, config, contexts, output))
    {
        m_refreshRate = 144;

        m_codeEditor = std::make_shared<CodeEditor>(m_config->projectPackage, "Code Editor");
        m_fileTreeContent = std::make_shared<FileTreeContent>();

        m_projectManager->SetCodeEditor(m_codeEditor);
        m_projectManager->SetFileTreeContent(m_fileTreeContent);

        m_window.SetContexts(m_contexts);
        m_window.SetProjectManager(m_projectManager);

        m_window.SetCodeEditor(m_codeEditor);
        m_window.SetFileTreeContent(m_fileTreeContent);
    }

    Application::~Application()
    {
        m_contexts->Clear();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Application::Start()
    {
        m_start = SDL_GetTicks();
        m_last = m_start;

        m_running = true;

        m_projectManager->Run();

        Run();
    }

    void Application::Run()
    {
        SDL_Event event;

        unsigned long long lastUPS = m_start;
        unsigned int ups = 0;

        unsigned long long lastFPS = m_start;
        unsigned int fps = 0;

        double lag = 0.0;
        const double secondsPerUpdate = 1.0 / UPS; // 50 UPS

        //---

        const int frameDelay = 1000 / m_refreshRate;

        //---

        int wheel = 0;
        //SDL_ShowCursor(SDL_DISABLE);
        
        while(m_running) 
        {
            SDL_PollEvent(&event);
            ImGui_ImplSDL2_ProcessEvent(&event);
            if(event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                m_running = false;
                break;
            }
            else if(event.type == SDL_WINDOWEVENT)
            {
                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    m_window.Resize(event.window.data1, event.window.data2);
                }
            }
            else if(event.type == SDL_MOUSEWHEEL)
            {
                wheel = event.wheel.y;
            }


            // Chronos
            unsigned long long now = SDL_GetTicks();
            unsigned long long elapsed = now - m_last;

            lag += (double) (elapsed) / 1000.0;
            
            while (lag > secondsPerUpdate)
            {
                // Mouse
                int mouseX, mouseY;
                const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
                
                //--- 
                   
                m_window.Update(lag);
                try
                {
                    Update(lag);
                }
                catch(const CodeException &e)
                {
                    *m_output << e.what();
                }

                m_window.SetMouseProps(ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY)), buttons, wheel);

                lag -= secondsPerUpdate;
                ups++;

                if (now - lastUPS >= 1000)
                {
                    lastUPS = SDL_GetTicks();
                    m_window.SetUPS(ups);
                    
                    ups = 0;
                }
            }
            m_last = SDL_GetTicks();
            
            m_window.Render(1.0 / lastFPS);

            fps++;

            if (now - lastFPS >= 1000)
            {
                lastFPS = SDL_GetTicks();
                m_window.SetFPS(fps);
                fps = 0;
            }
        }
    }

    void Application::Update(double lag)
    {
        m_projectManager->Update(lag);
        m_contexts->Update(lag);
    }

}