//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_ERROR_H
#define ARCPOSITION_ERROR_H

#include <string>
#include <SDL2/SDL.h>

namespace Math4BG
{
    int ShowErrorMessage(const std::string &message);
    void Beep();
    void Success();
}
#endif //ARCPOSITION_ERROR_H
