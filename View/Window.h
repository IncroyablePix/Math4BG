//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_WINDOW_H
#define ARCPOSITION_WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include "Screen.h"
#include "Renderer/IRenderer.h"
#include "../Transformers/WorldType.h"

#define UPS     50


namespace Math4BG
{
    struct WindowInfo
    {
        std::string title;
        unsigned int width;
        unsigned int height;
    };

    class Window : public std::enable_shared_from_this<Window>
    {
    public:
        Window(const WindowInfo &info, WorldType worldType);

        ~Window();

        static std::shared_ptr<Window> Create(const WindowInfo &info, WorldType worldType);

        inline std::shared_ptr<IRenderer> GetRenderer()
        { return m_renderer; }

        void SetFPS(unsigned int fps);

        void SetUPS(unsigned int ups);

        void Clear();
        void Draw(MainCamera* camera, IDrawable* drawable);
        void SwapBuffers();

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
        std::shared_ptr<IRenderer> m_renderer;

        std::string m_title;
        unsigned int m_fps;
        unsigned int m_ups;

        void UpdateWindowTitle();

        static std::shared_ptr<IRenderer> CreateRenderer(SDL_Window *window, unsigned int width, unsigned int height, WorldType worldType);
        static uint32_t FlagsFor(WorldType worldType);

        static void InitSDL();
    };

    static bool sdlInitialized = false;
}

#endif //ARCPOSITION_WINDOW_H
