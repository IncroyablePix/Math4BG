//
// Created by Benjam on 12-05-21.
//

#ifndef MATH4BG_IOUTPUT_H
#define MATH4BG_IOUTPUT_H

#include <iostream>
#include <memory>
#include <sstream>
#include "CircularQueue.h"

namespace Math4BG
{
    class IOutput : private std::streambuf, public std::ostream, public std::enable_shared_from_this<IOutput>
    {
    public:
        IOutput(const IOutput &output);
        ~IOutput() override = default;
        virtual void PrintMessages() = 0;

        template<typename T>
        std::ostream& operator<<(const T& data_)
        {
            std::stringstream ss;
            ss << data_;
            m_messages.push_back(ss.str());

            m_outStream << data_;

            return *this;
        }

    protected:
        IOutput();
        IOutput(std::ostream &outStream);
        std::ostream &m_outStream;
        CircularQueue<std::string> m_messages;
    };
}

#endif //MATH4BG_IOUTPUT_H
