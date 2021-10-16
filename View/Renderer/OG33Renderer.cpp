//
// Created by Benjam on 10/16/2021.
//

#include "OG33Renderer.h"

namespace Math4BG
{

    OG33Renderer::OG33Renderer(int width, int height) : m_width(width), m_height(height)
    {

    }

    OG33Renderer::~OG33Renderer()
    {

    }

    void OG33Renderer::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
    {
        m_background = { Col(r), Col(g), Col(b), 1.0f };
        glClearColor(m_background.r, m_background.g, m_background.b, m_background.a);
    }

    void OG33Renderer::Draw(ICamera *camera, IDrawable *drawable)
    {
        drawable->Bind(*camera);
    }

    void OG33Renderer::Clear()
    {
        glClearColor(m_background.r, m_background.g, m_background.b, m_background.a);
        //glClearColor(1.0f, 0.0, 0.0, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::shared_ptr<OG33Renderer> OG33Renderer::Create(int width, int height)
    {
        return std::shared_ptr<OG33Renderer>(static_cast<OG33Renderer *>(new OG33Renderer(width, height)));
    }

    float OG33Renderer::Col(uint32_t color)
    {
        return ((float) color) / 0xFF;
    }

    void OG33Renderer::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;
    }
}