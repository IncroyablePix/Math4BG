//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_WINDOW_H
#define ARCPOSITION_WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include "Screen.h"
#include "Renderer.h"

#define UPS     50

struct WindowInfo
{
    std::string title;
    unsigned int width;
    unsigned int height;
};

class Window : public std::enable_shared_from_this<Window>
{
public:
    Window(const WindowInfo &info);
    ~Window();
    static std::shared_ptr<Window> Create(const WindowInfo &info);
    inline std::shared_ptr<Renderer> GetRenderer()
    {
        return m_renderer;
    }
    void SetFPS(unsigned int fps);
    void SetUPS(unsigned int ups);
    void Draw();


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::shared_ptr<Renderer> m_renderer;

    std::string m_title;
    unsigned int m_fps;
    unsigned int m_ups;

    void UpdateWindowTitle();
};


#endif //ARCPOSITION_WINDOW_H
