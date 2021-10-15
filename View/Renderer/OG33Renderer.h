//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_OG33RENDERER_H
#define MATH4BG_OG33RENDERER_H


#include <memory>
#include <SDL2/SDL.h>
#include "../Screen.h"
#include "Draw/IDrawable.h"
#include "3D/Camera/ICamera.h"
#include "3D/Camera/MainCamera.h"


namespace Math4BG
{
    class OG33Renderer : public std::enable_shared_from_this<OG33Renderer>
    {
    public:
        OG33Renderer(SDL_Window *window, unsigned int width, unsigned int height);

        virtual ~OG33Renderer();

        inline unsigned int Width() const
        { return m_screen.width; }

        inline unsigned int Height() const
        { return m_screen.height; }

        virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

        virtual void Draw(ICamera* camera, IDrawable* drawable);
        virtual void Clear();
        static std::shared_ptr<OG33Renderer> Create(SDL_Window *window, unsigned int width, unsigned int height);

        inline void MakeContextCurrent(SDL_Window* window)
        {
            SDL_GL_MakeCurrent(window, m_glContext);
        }

    protected:
        Pixel m_background;
        Screen m_screen;

        SDL_GLContext m_glContext;

    private:
        static float Col(uint32_t color);
        static void GlewInitAttempt();
    };

    static bool glewInitialized = false;
}

#endif //MATH4BG_OG33RENDERER_H
