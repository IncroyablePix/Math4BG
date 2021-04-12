//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXT_H
#define ARCPOSITION_CONTEXT_H

#include <string>
#include <memory>
#include "../View/Window.h"
#include "World.h"

enum WorldType : uint32_t
{
    Flat
};

class Context
{
public:
    Context(const WindowInfo& info, WorldType type);//const std::string& title, unsigned int width, unsigned int height, WorldType worldType);
    ~Context();

    void Update();
    void SetUPS(int ups);
    void SetFPS(int fps);

    void Draw();

    inline World* GetWorld() { return m_world.get(); }

private:
    std::shared_ptr<Window> m_window;
    std::shared_ptr<World> m_world;
};


#endif //ARCPOSITION_CONTEXT_H
