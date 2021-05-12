//
// Created by Benjam on 12-05-21.
//

#include "IOutput.h"

namespace Math4BG
{
    IOutput::IOutput(std::ostream &outStream) : m_outStream(outStream)
    {

    }

    IOutput::IOutput(const IOutput  &output) : m_outStream(output.m_outStream)
    {
    }
}