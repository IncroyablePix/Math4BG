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
        virtual void Resize(int width, int height) = 0;
        inline unsigned int GetFPS() const { return m_fps; }

    protected:
        std::string m_title;
        unsigned int m_fps;
        unsigned int m_ups;
        int m_width;
        int m_height;
        virtual void UpdateWindowTitle() = 0;
    };
}

#endif //MATH4BG_IWINDOW_H
