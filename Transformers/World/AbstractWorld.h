//
// Created by Benjam on 11/6/2021.
//

#ifndef MATH4BG_ABSTRACTWORLD_H
#define MATH4BG_ABSTRACTWORLD_H


#include "IWorld.h"

namespace Math4BG
{
    class AbstractWorld : public IWorld
    {
    public:
        AbstractWorld(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer);
        void Draw(const std::string &title) override;
        void Update(double lag) override;

    private:
        float m_width;
        float m_height;
    };
}

#endif //MATH4BG_ABSTRACTWORLD_H
