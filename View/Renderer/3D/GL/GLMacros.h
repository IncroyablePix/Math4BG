//
// Created by Benjam on 13-04-21.
//

#ifndef MATH4BG_GLMACROS_H
#define MATH4BG_GLMACROS_H

#define ASSERT(x)       if(!(x))__debugbreak();
#define GLCall(x)       GLClearError(); \
                        x;              \
                        ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace Math4BG
{
    void GLClearError();
    bool GLLogCall(const char *function, const char *file, int line);
}

#endif //MATH4BG_GLMACROS_H
