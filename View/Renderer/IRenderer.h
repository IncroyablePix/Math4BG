//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_IRENDERER_H
#define MATH4BG_IRENDERER_H


#include <memory>
#include <SDL2/SDL.h>
#include "../Screen.h"
#include "Draw/IDrawable.h"
#include "3D/Camera/ICamera.h"
#include "3D/Camera/MainCamera.h"


namespace Math4BG
{
    class IRenderer : public std::enable_shared_from_this<IRenderer>
    {
    public:
        IRenderer(SDL_Window *window, unsigned int width, unsigned int height);

        virtual ~IRenderer();

        inline unsigned int Width() const
        { return m_screen.width; }

        inline unsigned int Height() const
        { return m_screen.height; }

        virtual void SwapBuffers() = 0;

        virtual void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

        virtual void Draw(MainCamera* camera, IDrawable* drawable) = 0;
        virtual void Clear() = 0;

    protected:
        Pixel m_background;
        Screen m_screen;
    };
}

#endif //MATH4BG_IRENDERER_H
