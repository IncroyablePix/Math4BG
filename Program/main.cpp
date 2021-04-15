#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "Application.h"
#include "../View/Error.h"
#include <memory>

int main(int argc, char** argv)
{
    Math4BG::Config config;
    LoadConfig(CONFIG_PATH, config);

    //---

    /*WindowInfo info = { "Math vision", 1280, 720 };
    std::shared_ptr<Window> window = Window::Create(info);*/

    std::shared_ptr<Math4BG::Contexts> contexts = Math4BG::Contexts::Create();

    Math4BG::Application app(contexts, config);
    try
    {
        app.Start();
    }
    catch(std::runtime_error& e)
    {
        Math4BG::ShowErrorMessage(e.what());
    }

    return EXIT_SUCCESS;
}
