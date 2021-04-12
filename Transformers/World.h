//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_WORLD_H
#define ARCPOSITION_WORLD_H


#include <memory>
#include <unordered_map>
#include "../View/Renderer.h"
#include "Shapes.h"

class World
{
public:
    World(std::shared_ptr<Renderer>  renderer);
    ~World();

    void Update();

    int CreateCircle(Point center, double radius, uint32_t color);
    bool SetCirclePos(int circleid, Point center);
    bool SetCircleSize(int circleid, double radius);
    bool SetCircleColor(int circleid, uint32_t color);

    int CreateLine(Point start, Point end, uint32_t color);
    bool SetLinePos(int lineid, Point start, Point end);
    bool SetLineColor(int lineid, uint32_t color);

private:
    std::shared_ptr<Renderer> m_renderer;

    std::unordered_map<int, Circle> m_circles;
    std::unordered_map<int, Line> m_lines;

    int m_count = 0;
};


#endif //ARCPOSITION_WORLD_H
