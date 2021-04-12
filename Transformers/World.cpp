//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include "World.h"

World::World(std::shared_ptr<Renderer> renderer) :
m_renderer(std::move(renderer))
{

}

World::~World()
{

}

void World::Update()
{
    m_renderer->Clear();
    for(auto &circle : m_circles)
    {
        Circle c = circle.second;
        m_renderer->DrawEllipse(c.center.x, c.center.y, c.radius, c.radius, c.color);
    }

    for(auto & line : m_lines)
    {
        Line l = line.second;
        m_renderer->DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, l.color);
    }
}

int World::CreateCircle(Point center, double radius, uint32_t color)
{
    m_circles[m_count] = { center, radius, color };
    return m_count ++;
}

bool World::SetCirclePos(int circleid, Point center)
{
    if(m_circles.find(circleid) != m_circles.end())
    {
        m_circles[circleid].center.x = center.x;
        m_circles[circleid].center.y = center.y;
        return true;
    }

    return false;
}

bool World::SetCircleSize(int circleid, double radius)
{
    if(m_circles.find(circleid) != m_circles.end())
    {
        m_circles[circleid].radius = radius;
        return true;
    }

    return false;
}

bool World::SetCircleColor(int circleid, uint32_t color)
{
    if(m_circles.find(circleid) != m_circles.end())
    {
        m_circles[circleid].color = color;
        return true;
    }

    return false;
}

int World::CreateLine(Point start, Point end, uint32_t color)
{
    m_lines[m_count] = { start, end, color };
    return m_count ++;
}

bool World::SetLinePos(int lineid, Point start, Point end)
{
    if(m_lines.find(lineid) != m_lines.end())
    {
        m_lines[lineid].start = start;
        m_lines[lineid].end = end;
        return true;
    }

    return false;
}

bool World::SetLineColor(int lineid, uint32_t color)
{
    if(m_lines.find(lineid) != m_lines.end())
    {
        m_lines[lineid].color = color;
        return true;
    }

    return false;
}
