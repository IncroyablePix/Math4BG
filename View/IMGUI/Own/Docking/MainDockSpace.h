//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_MAINDOCKSPACE_H
#define MATH4BG_MAINDOCKSPACE_H

#include "DockSpace.h"

namespace Math4BG
{
    class MainDockSpace : public DockSpace
    {
    public:
        MainDockSpace(const std::string &title, ImGuiID dockspaceId);
        ~MainDockSpace();
        void Show() override;
    };
}

#endif //MATH4BG_MAINDOCKSPACE_H
