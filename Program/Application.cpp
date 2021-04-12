//
// Created by Benjam on 11-04-21.
//

#include <iostream>
#include "Application.h"

Application::Application(const std::shared_ptr<Window>& window, const Config &config) :
m_window(std::shared_ptr(window)),
m_luaInterpreter(std::make_shared<LuaInterpreter>())
{
    m_logic = std::make_shared<Logic>(window->GetRenderer());
    m_world = std::make_shared<World>(window->GetRenderer());

    m_luaInterpreter->SetWorld(m_world);
    m_luaInterpreter->ExecuteFile(config.scriptFile);
}

Application::~Application()
{

}

void Application::Start()
{
    m_start = SDL_GetTicks();
    m_last = m_start;

    m_running = true;

    if(!m_luaInterpreter->CheckValidity())
        throw std::runtime_error("Invalid Lua script :\nMust contain the following functions : OnInit, OnUpdate(number)");

    m_luaInterpreter->CallOnInitFunction();
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

    while (m_running)
    {
        //---SDL STUFF---//
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                m_running = false;
        }

        //---LOGIC UPDATE---//
        unsigned long long now = SDL_GetTicks();
        unsigned long long elapsed = now - m_last;

        lag += (double) (elapsed) / 1000.0;

        while(lag > secondsPerUpdate) {
            Update(lag);

            lag -= secondsPerUpdate;
            ups ++;

            if(now - lastUPS >= 1000)
            {
                lastUPS = SDL_GetTicks();
                m_window->SetUPS(ups);
                ups = 0;
            }
        }
        m_last = SDL_GetTicks();

        m_window->Draw();
        fps++;

        if (now - lastFPS >= 1000)
        {
            lastFPS = SDL_GetTicks();
            m_window->SetFPS(fps);
            fps = 0;
        }

        //SDL_UpdateWindowSurface(m_window.get());
    }
}

void Application::Update(double lag) {
    //m_logic->Update(lag);
    m_luaInterpreter->CallUpdateFunction(lag);
    m_world->Draw();
}