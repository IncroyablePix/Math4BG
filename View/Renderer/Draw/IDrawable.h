//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_IDRAWABLE_H
#define MATH4BG_IDRAWABLE_H

#include <memory>

namespace Math4BG
{
    class IDrawable : std::enable_shared_from_this<IDrawable>
    {
    public:
        virtual ~IDrawable() = default;
    };
}

#endif //MATH4BG_IDRAWABLE_H
