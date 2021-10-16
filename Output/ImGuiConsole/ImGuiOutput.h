//
// Created by Benjam on 10/16/2021.
//

#ifndef MATH4BG_IMGUIOUTPUT_H
#define MATH4BG_IMGUIOUTPUT_H

#include <vector>
#include <sstream>
#include "../IOutput.h"
#include "../CircularQueue.h"

namespace Math4BG
{
    class ImGuiOutput : public IOutput
    {
    public:
        ImGuiOutput();
        static std::shared_ptr<ImGuiOutput> Create();

        void PrintMessages() override;
    };
}

#endif //MATH4BG_IMGUIOUTPUT_H
