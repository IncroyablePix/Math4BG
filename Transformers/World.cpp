//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include "World.h"
#include "../View/Renderer/2D/Object/SinglePixel.h"


namespace Math4BG
{
    World::World(WorldType type, std::shared_ptr<IRenderer> renderer) :
            m_renderer(std::move(renderer)),
            m_type(type)
    {

    }

    World::~World()
    {

    }

    void World::Update()
    {
        /*for (auto &circle : m_circles)
        {
            Circle c = circle.second;
            m_renderer->DrawEllipse(c.center.x, c.center.y, c.radius, c.radius, c.color);
        }

        for (auto &line : m_lines)
        {
            Line l = line.second;
            m_renderer->DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, l.color);
        }*/

        /*for(auto &o : m_objects)
        {

        }*/
    }

    int World::CreateCircle(Point center, double radius, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<Circle>(center, radius, color);
            //m_circles[m_count] = {center, radius, color};
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    bool World::SetCirclePos(int circleid, Point center)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->m_center.x = center.x;
                c->m_center.y = center.y;
                return true;
            }
        }

        return false;
    }

    bool World::SetCircleSize(int circleid, double radius)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->m_radius = radius;
                return true;
            }
        }

        return false;
    }

    bool World::SetCircleColor(int circleid, uint32_t color)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->SetColor(color);
                return true;
            }
        }

        return false;
    }

    int World::CreateLine(Point start, Point end, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<Line>(start, end, color);
            //m_lines[m_count] = { start, end, color };
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    bool World::SetLinePos(int lineid, Point start, Point end)
    {
        if (m_lines.find(lineid) != m_lines.end())
        {
            m_lines[lineid].m_start = start;
            m_lines[lineid].m_end = end;
            return true;
        }

        return false;
    }

    bool World::SetLineColor(int lineid, uint32_t color)
    {
        if (m_lines.find(lineid) != m_lines.end())
        {
            m_lines[lineid].SetColor(color);
            return true;
        }

        return false;
    }

    void World::SetBackgroundColor(unsigned int color)
    {
        uint8_t r = color >> 6;
        uint8_t g = color >> 4;
        uint8_t b = color >> 2;


        m_renderer->SetBackgroundColor(r, g, b);
    }

    void World::Draw(Window &window)
    {
        for(const auto& drawable : m_objects)
            window.Draw(drawable.second.get());
    }

    int World::CreateDot(Point position, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<SinglePixel>(position, color);
            //m_circles[m_count] = {center, radius, color};
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
        return 0;
    }

    bool World::SetDotColor(int dotid, uint32_t color)
    {
        if (m_objects.find(dotid) != m_objects.end())
        {
            auto circle = m_objects[dotid].get();
            if(SinglePixel* p = dynamic_cast<SinglePixel*>(circle))
            {
                p->SetColor(color);
                return true;
            }
        }

        return false;
    }
}