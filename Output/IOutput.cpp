//
// Created by Benjam on 12-05-21.
//

#include "IOutput.h"

namespace Math4BG
{
    IOutput::IOutput(std::ostream &outStream) : m_outStream(outStream), m_messages(250)
    {

    }

    IOutput::IOutput(const IOutput  &output) : m_outStream(output.m_outStream), m_messages(250)
    {
    }

    IOutput::IOutput() : m_outStream(std::cout), m_messages(250)
    {

    }
}