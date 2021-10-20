//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_IGUIELEMENT_H
#define MATH4BG_IGUIELEMENT_H

#include <memory>

namespace Math4BG
{
    class IGuiElement : public std::enable_shared_from_this<IGuiElement>
    {
    public:
        virtual void Show() = 0;
        virtual const std::string& GetName() = 0;
    };
}

#endif //MATH4BG_IGUIELEMENT_H
