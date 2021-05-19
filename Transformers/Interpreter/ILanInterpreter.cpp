//
// Created by Benjam on 19-05-21.
//

#include "ILanInterpreter.h"

#include <utility>

namespace Math4BG
{

    ILanInterpreter::ILanInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output) :
    m_contexts(std::move(contexts)),
    m_output(std::move(output))
    {

    }
}