//
// Created by Benjam on 11/6/2021.
//

#ifndef MATH4BG_CONCRETEWORLD_H
#define MATH4BG_CONCRETEWORLD_H

#include "IWorld.h"

namespace Math4BG
{
    class ConcreteWorld : public IWorld
    {
    public:
        ConcreteWorld(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer);
        void Draw(const std::string &title) override;
        void Update(double lag) override;

        void HandleMouseInputs();
        void HandleKeyboardInputs();

    private:
        bool m_tabActive;

        MouseInput m_mouse;
        KeyInput m_keys;
    };
}

#endif //MATH4BG_CONCRETEWORLD_H
