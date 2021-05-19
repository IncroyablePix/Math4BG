//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_RENDERER_H
#define ARCPOSITION_RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include "../../Screen.h"
#include "../IRenderer.h"


namespace Math4BG
{
    class Renderer2D : public IRenderer
    {
    public:
        Renderer2D(SDL_Window *window, unsigned int width, unsigned int height);

        ~Renderer2D() override;

        static std::shared_ptr<Renderer2D> Create(SDL_Window *window, unsigned int width, unsigned int height);

        void Draw(MainCamera *camera, IDrawable* drawable) override;
        void Clear() override;
        void SwapBuffers() override;

        /*void DrawLine(int x0, int y0, int x1, int y1, uint32_t argb) override;
        void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t argb) override;
        void DrawRect(int x0, int y0, int width, int height, uint32_t argb) override;
        void DrawEllipse(int x0, int y0, int xRadius, int yRadius, uint32_t argb) override;
        void SetPixel(int x, int y, uint32_t argb) override;*/

    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
        SDL_Rect m_screenRectangle;

        void ny(int &y);
    };
}

#endif //ARCPOSITION_RENDERER_H
