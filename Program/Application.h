//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_APPLICATION_H
#define ARCPOSITION_APPLICATION_H


#include "../Transformers/Logic.h"
#include "../View/Window.h"
#include "../Transformers/LuaInterpreter.h"
#include "Config/Config.h"
#include "../Transformers/Context.h"
#include "../Transformers/Contexts.h"

class Application
{
public:
    Application(std::shared_ptr<Contexts> contexts, const Config& config);
    ~Application();
    void Start();



private:
    std::shared_ptr<Contexts> m_contexts;
    std::shared_ptr<LuaInterpreter> m_luaInterpreter;
    unsigned long long m_start;
    unsigned long long m_last;
    bool m_running;

    void Update(double lag);
    void Run();
};


#endif //ARCPOSITION_APPLICATION_H
