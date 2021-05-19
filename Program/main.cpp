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
    LoadConfig(CONFIG_PATH, config);

    //---
    std::shared_ptr<Math4BG::IOutput> out = Math4BG::TerminalOutput::Create();
    std::shared_ptr<Math4BG::Contexts> contexts = Math4BG::Contexts::Create();

    Math4BG::Application app(contexts, config, out);

    try
    {
        app.Start();
    }
    catch(std::runtime_error& e) // Terrible idea : To remove someday (maybe)
    {
        Math4BG::ShowErrorMessage(e.what());
    }

    return EXIT_SUCCESS;
}
