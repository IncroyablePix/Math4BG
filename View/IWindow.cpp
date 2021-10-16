//
// Created by Benjam on 8/1/2021.
//

#include "IWindow.h"

namespace Math4BG
{
    IWindow::IWindow(const WindowInfo &info) : m_title(info.title), m_width(info.width), m_height(info.height)
    {

    }

    void IWindow::SetFPS(unsigned int fps)
    {
        m_fps = fps;
    }

    void IWindow::SetUPS(unsigned int ups)
    {
        m_ups = ups;
        UpdateWindowTitle();
    }
}