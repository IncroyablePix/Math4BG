//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include "Error.h"

#if defined(_WIN64) || defined(_WIN32)
    #include <windows.h>
#elif !defined(_WIN32) && defined(__UNIX__)

#elif defined(__APPLE__)

#endif

namespace Math4BG
{
    int ShowErrorMessage(const std::string &message)
    {
        return SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unhandled error", message.c_str(), nullptr);
    }

    void Beep()
    {
        std::cout << '\a' << std::flush;
    }

    void Success()
    {

    }
}