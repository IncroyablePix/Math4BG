//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_RENDERER_H
#define ARCPOSITION_RENDERER_H

#include <SDL2/SDL.h>
#include <memory>
#include "Screen.h"

class Renderer : public std::enable_shared_from_this<Renderer>
{
public:
    Renderer(SDL_Window* window, unsigned int width, unsigned int height);
    ~Renderer();
    static std::shared_ptr<Renderer> Create(SDL_Window* window, unsigned int width, unsigned int height);

    void Draw();

    //---

    void Clear();

    void SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

    void DrawLine(int x0, int y0, int x1, int y1, uint32_t argb);
    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t argb);
    void DrawRect(int x0, int y0, int width, int height, uint32_t argb);
    void DrawEllipse(int x0, int y0, int xRadius, int yRadius, uint32_t argb);
    void SetPixel(int x, int y, uint32_t argb);

    //---

    inline unsigned int Width()
    {
        return m_screen.width;
    }

    inline unsigned int Height()
    {
        return m_screen.height;
    }

private:
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
    SDL_Rect m_screenRectangle;
    Screen m_screen;
    Pixel m_background;

    template<typename T>
    void Swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    void ny(int &y);
};


#endif //ARCPOSITION_RENDERER_H
