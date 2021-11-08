//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXT_H
#define ARCPOSITION_CONTEXT_H

#include "World/IWorld.h"
#include "World/WorldType.h"
#include <string>
#include <memory>
#include "../View/Window.h"
#include "../Input/MouseInput.h"
#include "../Input/KeyInput.h"
#include "../View/Renderer/OG33Renderer.h"

namespace Math4BG
{
    class Context : public std::enable_shared_from_this<Context>
    {
    public:
        explicit Context(const WindowInfo &info, bool abstract = false);
        ~Context();

        void Update(double lag);
        void Draw();

        inline std::shared_ptr<IWorld> GetWorld() { return m_world; }
        inline unsigned int GetFboId() const { return m_world->GetFboId(); }
        inline std::shared_ptr<Texture> GetFboTexture() const { return m_world->GetFboTexture(); }
        inline const std::string& GetTitle() const { return m_title; }

    private:
        //std::shared_ptr<Window> m_window;
        std::shared_ptr<IWorld> m_world;
        std::shared_ptr<OG33Renderer> m_renderer;
        std::string m_title;
    };
}


#endif //ARCPOSITION_CONTEXT_H
