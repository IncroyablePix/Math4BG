//
// Created by Benjam on 12-05-21.
//

#ifndef MATH4BG_TERMINALOUTPUT_H
#define MATH4BG_TERMINALOUTPUT_H


#include "../IOutput.h"
#include "../../View/IMGUI/Own/IGuiElement.h"

namespace Math4BG
{
    class TerminalOutput : public IOutput
    {
    public:
        TerminalOutput();
        static std::shared_ptr<TerminalOutput> Create();

        void PrintMessages() override { }
    };
}

#endif //MATH4BG_TERMINALOUTPUT_H
