//
// Created by Benjam on 8/1/2021.
//

#ifndef MATH4BG_IWINDOW_H
#define MATH4BG_IWINDOW_H

#include <memory>

namespace Math4BG
{
    struct WindowInfo
    {
        std::string title;
        unsigned int width;
        unsigned int height;
    };

    class IWindow : public std::enable_shared_from_this<IWindow>
    {
    public:
        IWindow(const WindowInfo &info);
        void SetFPS(unsigned int fps);
        void SetUPS(unsigned int ups);

    protected:
        std::string m_title;
        unsigned int m_fps;
        unsigned int m_ups;
        virtual void UpdateWindowTitle() = 0;
    };
}

#endif //MATH4BG_IWINDOW_H
