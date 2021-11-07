//
// Created by Benjam on 11/6/2021.
//

#include "AbstractWorld.h"

#include <utility>

namespace Math4BG
{
    AbstractWorld::AbstractWorld(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer) :
    IWorld(info,std::move(renderer)),
    m_width(info.width),
    m_height(info.height)
    {

    }

    void AbstractWorld::Draw(const std::string &title)
    {
        m_camera->SetViewportSize(m_width, m_height);
        DrawWorld();

        //m_canvas.Bind(*m_ppShader, *m_fbo.GetTexture()); // Drawing frame buffer over canvas
    }

    void AbstractWorld::Update(double lag)
    {

    }
}