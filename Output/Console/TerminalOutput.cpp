//
// Created by Benjam on 12-05-21.
//

#include "TerminalOutput.h"

namespace Math4BG
{
    TerminalOutput::TerminalOutput() : IOutput(std::cout)
    {

    }

    std::shared_ptr<TerminalOutput> TerminalOutput::Create()
    {
        return std::make_shared<TerminalOutput>();
    }
}
