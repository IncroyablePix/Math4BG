//
// Created by Benjam on 12-04-21.
//

#include "Error.h"

int ShowErrorMessage(const std::string& message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unhandled error", message.c_str(), nullptr);
}