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

namespace Math4BG
{
    Application::Application(const WindowInfo &info, std::shared_ptr<Contexts> contexts, const Config &config, std::shared_ptr<IOutput> output) :
        m_interpreter(CreateInterpreter("lua", contexts, output)),
        m_fpsLimiter(config.fpsLimiter),
        m_window(info, output),
        m_output(std::move(output))
    {
        /*WindowInfo info {"Math4BG", 1280, 720};
        m_window = std::make_unique<MainWindow>(info, output);*/
        /*SDL_DisplayMode current;
        int errorCode = SDL_GetCurrentDisplayMode(0, &current);
        if(errorCode != 0)
            throw std::runtime_error("Could not retrieve DisplayMode");*/

        m_refreshRate = 144;

        m_contexts = std::shared_ptr<Contexts>(std::move(contexts));
        m_interpreter->ExecuteFile(config.scriptFile);

        m_window.SetContexts(m_contexts);
    }

    Application::~Application()
    {
        ImGui::DestroyContext();
    }

    void Application::Start()
    {
        m_start = SDL_GetTicks();
        m_last = m_start;

        m_running = true;

        if (!m_interpreter->CheckValidity())
            throw std::runtime_error(
                    "Invalid Lua script :\nMust contain the following functions : OnInit, OnUpdate(number), OnWindowClosed(windowId)");

        m_interpreter->CallOnInitFunction();
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
                Update(lag);
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
            
            m_window.Render();

            fps++;

            if (now - lastFPS >= 1000)
            {
                lastFPS = SDL_GetTicks();
                m_window.SetFPS(fps);
                fps = 0;
            }
        }

        /*while (m_running)
        {
            ImGuiIO& io = ImGui::GetIO();
            //---SDL STUFF---//
            SDL_PollEvent(&event);
            ManageWindowEvents(event);

            //---LOGIC UPDATE---//
            std::unordered_map<int, Context *>::iterator it;
            std::unordered_map<int, Context *>::iterator itEnd;

            unsigned long long now = SDL_GetTicks();
            unsigned long long elapsed = now - m_last;

            lag += (double) (elapsed) / 1000.0;

            while (lag > secondsPerUpdate)
            {
                Update(lag);

                lag -= secondsPerUpdate;
                ups++;

                if (now - lastUPS >= 1000)
                {
                    lastUPS = SDL_GetTicks();

                    it = m_contexts->Begin();
                    for (; it != itEnd; it++)
                        it->second->SetUPS(ups);

                    ups = 0;
                }
            }
            m_last = SDL_GetTicks();

            m_window->Render();// TODO : ?

            it = m_contexts->Begin();
            for (; it != itEnd; it++)
            {
                if(it->second)
                    it->second->Draw();
            }

            fps++;

            if (now - lastFPS >= 1000)
            {
                lastFPS = SDL_GetTicks();

                it = m_contexts->Begin();
                for (; it != itEnd; it++)
                {
                    if(it->second)
                        it->second->SetFPS(fps);
                }
                fps = 0;
            }

            if(m_fpsLimiter)
            {
                unsigned long long frameTime = SDL_GetTicks() - m_last;
                if (frameDelay > frameTime)
                    SDL_Delay(frameDelay - frameTime);
            }
        }*/
    }

    void Application::ManageWindowEvents(const SDL_Event& event)
    {
        int windowId = event.window.windowID;
        /*Context* context = m_contexts->ContextFromWindowId(windowId);

        switch (event.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(context)
                    context->MouseSet(Mouse.ConvertSDLInput(event.button.button), true);
                break;
            case SDL_MOUSEBUTTONUP:
                if(context)
                    context->MouseSet(Mouse.ConvertSDLInput(event.button.button), false);
                break;
            case SDL_MOUSEMOTION:
                if(context)
                    context->MousePos({ event.motion.x, event.motion.y });
                break;
            case SDL_KEYDOWN:
                if(context)
                    context->KeySet(Keys.ConvertSDLInput(event.key.keysym.sym), true);
                break;
            case SDL_KEYUP:
                if(context)
                    context->KeySet(Keys.ConvertSDLInput(event.key.keysym.sym), false);
                break;
            case SDL_WINDOWEVENT:
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        windowId = m_contexts->KillContextForWindowId(event.window.windowID);
                        m_interpreter->CallOnWindowClosed(windowId);
                        break;
                }
                break;
        }*/
    }

    void Application::Update(double lag)
    {
        //Mouse.Update();
        //Keys.Update();
        //std::cout << Mouse.Position().x << ", " << Mouse.Position().y << " - " << Mouse.DeltaPosition().x << ", " << Mouse.DeltaPosition().y << std::endl;

        std::unordered_map<int, Context *>::iterator it;
        std::unordered_map<int, Context *>::iterator itEnd;

        m_interpreter->CallUpdateFunction(lag);

        it = m_contexts->Begin();
        for (; it != itEnd; it++)
        {
            if(it->second)
            {
                it->second->Update(lag);
            }
        }
    }

    std::shared_ptr<ILanInterpreter> Application::CreateInterpreter(const std::string &name, std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output)
    {
        if(name == "lua")
            return std::shared_ptr<ILanInterpreter>(LuaInterpreter::Create(std::move(contexts), std::move(output)));
        /*else if(name == "js")
            return std::shared_ptr<ILanInterpreter>(JavascriptInterpreter::Create(contexts, output));*/

        throw std::runtime_error("Invalid Interpreter specified!");
    }
}