//
// Created by Benjam on 19-05-21.
//

#ifndef MATH4BG_ILANINTERPRETER_H
#define MATH4BG_ILANINTERPRETER_H

#include <string>
#include <memory>
#include "../Contexts.h"
#include "../../Output/IOutput.h"

namespace Math4BG
{
    class ILanInterpreter : std::enable_shared_from_this<ILanInterpreter>
    {
    public:
        ILanInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        virtual ~ILanInterpreter() = default;

        virtual void ExecuteFile(const std::string &path) = 0;

        virtual int CallOnInitFunction() = 0;
        virtual int CallUpdateFunction(double lag) = 0;
        virtual int CallOnWindowClosed(int windowId) = 0;

        virtual bool CheckValidity() = 0;
        virtual void RegisterFunctions() = 0;

    protected:
        std::shared_ptr<IOutput> m_output;
        std::shared_ptr<Contexts> m_contexts;
    };
}

#endif //MATH4BG_ILANINTERPRETER_H
