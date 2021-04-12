//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_APPLICATION_H
#define ARCPOSITION_APPLICATION_H


#include "../Transformers/Logic.h"
#include "../View/Window.h"
#include "../Transformers/LuaInterpreter.h"
#include "Config/Config.h"

class Application
{
public:
    Application(const std::shared_ptr<Window>& window, const Config& config);
    ~Application();
    void Start();

private:
    std::shared_ptr<Logic> m_logic;
    std::shared_ptr<Window> m_window;
    std::shared_ptr<LuaInterpreter> m_luaInterpreter;
    std::shared_ptr<World> m_world;
    unsigned long long m_start;
    unsigned long long m_last;
    bool m_running;

    void Update(double lag);
    void Run();
};


#endif //ARCPOSITION_APPLICATION_H
