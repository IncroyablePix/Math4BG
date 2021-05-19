//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXT_H
#define ARCPOSITION_CONTEXT_H

#include <string>
#include <memory>
#include "../View/Window.h"
#include "World.h"
#include "WorldType.h"

namespace Math4BG
{
    class Context
    {
    public:
        Context(const WindowInfo &info, WorldType type);
        ~Context();

        void Update(double lag);

        void SetUPS(int ups);

        void SetFPS(int fps);

        void Draw();

        inline World *GetWorld() { return m_world.get(); }

        inline uint32_t GetWindowId() { return m_window->GetWindowId(); }

    private:
        std::shared_ptr<Window> m_window;
        std::shared_ptr<World> m_world;

    };
}


#endif //ARCPOSITION_CONTEXT_H
