#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "Application.h"
#include "../View/Error.h"
#include "../Output/Console/TerminalOutput.h"
#include "../Output/ImGuiConsole/ImGuiOutput.h"
#include <memory>

int main(int argc, char** argv)
{
    std::shared_ptr<Math4BG::Config> config = std::make_shared<Math4BG::Config>();

    try
    {
        LoadConfig(CONFIG_PATH, config);
    }
    catch(std::runtime_error &e)
    {
        Math4BG::ShowErrorMessage(e.what());
    }

    ParseArgs(argc, argv, config);

    //---


    std::shared_ptr<Math4BG::IOutput> out = Math4BG::ImGuiOutput::Create();
    std::shared_ptr<Math4BG::Contexts> contexts = Math4BG::Contexts::Create(out);

    Math4BG::Application app({ "Math4BG", 1280, 720 }, contexts, std::move(config), out);
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
