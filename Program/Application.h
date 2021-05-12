//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_APPLICATION_H
#define ARCPOSITION_APPLICATION_H


#include "../View/Window.h"
#include "../Transformers/LuaInterpreter.h"
#include "Config/Config.h"
#include "../Transformers/Context.h"
#include "../Transformers/Contexts.h"
#include "../Output/IOutput.h"

namespace Math4BG
{
    class Application
    {
    public:
        Application(std::shared_ptr<Contexts> contexts, const Config &config, std::shared_ptr<IOutput> output);
        ~Application();
        void Start();

    private:
        std::shared_ptr<Contexts> m_contexts;
        std::shared_ptr<LuaInterpreter> m_luaInterpreter;
        std::shared_ptr<IOutput> m_output;
        unsigned long long m_start;
        unsigned long long m_last;
        bool m_running;
        bool m_fpsLimiter;
        int m_refreshRate;

        void Update(double lag);

        void Run();
    };
}

#endif //ARCPOSITION_APPLICATION_H
