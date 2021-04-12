//
// Created by Benjam on 11-04-21.
//

#include "Logic.h"
#include "Shapes.h"
#include <cmath>
#include <iostream>

Logic::Logic(std::shared_ptr<Renderer> renderer) :
m_renderer(std::move(renderer))
{
    m_renderer->SetBackgroundColor(0x0, 0x0, 0x0);
}

Logic::~Logic()
{

}

void Logic::Update(double lag)
{
    static double elapsed = 0.0;
    elapsed += lag;

    int w = m_renderer->Width();
    int h = m_renderer->Height();

    Circle b1 = {175, 175, 160.0, CIRCLE_COLOR };
    Circle b2 = {400, 125, 125.0, CIRCLE_COLOR };

    double n = (-sqr(b1.center.x) - sqr(b1.center.y) + sqr(b2.center.x) + sqr(b2.center.y) + (b1.radius - b2.radius)) / (2 * (b2.center.y - b1.center.y));
    double m = (b2.center.x - b1.center.x) / (b2.center.y - b1.center.y);

    double a = sqr(m) + 1.0;
    double b = (-2 * b1.center.x) + (2 * b1.center.y) * m - (2 * n * m);
    double c = sqr(b1.center.x) + sqr(b1.center.y) - 2 * b1.center.y * n + sqr(n) - sqr(b1.radius);

    double delta = sqr(b) - 4 * a * c;

    double x1 = (-b + sqrt(delta)) / (2 * a);
    double x2 = (-b - sqrt(delta)) / (2 * a);
    double y1 = (n - x1 * m);
    double y2 = (n - x2 * m);

    Circle drone1 { x1, y1, 10, 0xFFFFFFFF };
    Circle drone2 { x2, y2, 10, 0xFFFFFFFF };

    //std::cout << "Drone1 : " << x1 << ", " << y1 << std::endl;
    //std::cout << "Drone2 : " << x2 << ", " << y2 << std::endl;

    //---

    m_renderer->Clear();

    //---//

    b1.Draw(m_renderer.get());
    b2.Draw(m_renderer.get());

    drone1.Draw(m_renderer.get());
    drone2.Draw(m_renderer.get());

    //---//



    /*
    m_renderer->DrawEllipse(w / 2, h / 2, 50, 50, 0xFFFFA500);
    m_renderer->DrawLine(0, 0, w, h, 0xFFFFFF00);
    m_renderer->DrawRect(10, 10, w - 20, h - 20, 0xFF00FFFF);
    m_renderer->DrawTriangle(20, h - 20, w / 2, 20, w - 20, h - 20, 0xFFFFFFFF);

    m_renderer->DrawEllipse(elapsed * 50, h / 3, 50, 50, 0xFFA511A5);*/
}

double Logic::sqr(double n)
{
    return n * n;
}
