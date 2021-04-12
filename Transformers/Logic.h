//
// Created by Benjam on 11-04-21.
//

#ifndef ARCPOSITION_LOGIC_H
#define ARCPOSITION_LOGIC_H


#include "../View/Renderer.h"
#include "Shapes.h"

class Logic
{
public:
    Logic(std::shared_ptr<Renderer>  renderer);
    ~Logic();
    void Update(double lag);

private:
    std::shared_ptr<Renderer> m_renderer;

    double first(Circle b1, Circle b2);

    double sqr(double n);

    double second(Circle b1, Circle b2);
};


#endif //ARCPOSITION_LOGIC_H
