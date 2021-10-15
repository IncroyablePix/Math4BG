//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_WINDOW_H
#define ARCPOSITION_WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include "Screen.h"
#include "Renderer/OG33Renderer.h"
#include "../Transformers/WorldType.h"
#include "IWindow.h"

#define UPS     50

namespace Math4BG
{
    class Window : public IWindow
    {
    public:
        Window(const WindowInfo &info, WorldType worldType);

        ~Window();

        static std::shared_ptr<Window> Create(const WindowInfo &info, WorldType worldType);

        inline std::shared_ptr<OG33Renderer> GetRenderer()
        { return m_renderer; }


        void Clear();
        void MakeCurrentContext();
        void Draw(MainCamera* camera, IDrawable* drawable);
        void DrawGUI();
        void SwapBuffers();

        inline uint32_t GetWindowId() { return SDL_GetWindowID(m_window.get()); }

    protected:
        void UpdateWindowTitle() override;

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
        std::shared_ptr<OG33Renderer> m_renderer;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_sdlRenderer;

        static std::shared_ptr<OG33Renderer> CreateRenderer(SDL_Window *window, unsigned int width, unsigned int height, WorldType worldType);
        static uint32_t FlagsFor(WorldType worldType);

        static void InitSDL();
    };

    static bool sdlInitialized = false;
}

#endif //ARCPOSITION_WINDOW_H
