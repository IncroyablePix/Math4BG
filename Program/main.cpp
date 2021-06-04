#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "Application.h"
#include "../View/Error.h"
#include "../Output/Console/TerminalOutput.h"
#include <memory>

int main(int argc, char** argv)
{
    Math4BG::Config config;
    try
    {
        LoadConfig(CONFIG_PATH, config);
    }
    catch(std::runtime_error &e)
    {
        Math4BG::ShowErrorMessage(e.what());
    }

    //--- TODO : Override params when passed as args to main

    ParseArgs(argc, argv, config);

    //---

    std::shared_ptr<Math4BG::IOutput> out = Math4BG::TerminalOutput::Create();
    std::shared_ptr<Math4BG::Contexts> contexts = Math4BG::Contexts::Create();

    Math4BG::Application app(contexts, config, out);

    try
    {
        app.Start();
    }
    catch(std::runtime_error& e) // Worst idea ever but whatever this is an pre-pre-pre-alpha : To put closer to actual errors, no time right now
    {
        Math4BG::ShowErrorMessage(e.what());
    }

    return EXIT_SUCCESS;
}
