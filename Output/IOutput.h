//
// Created by Benjam on 12-05-21.
//

#ifndef MATH4BG_IOUTPUT_H
#define MATH4BG_IOUTPUT_H

#include <iostream>
#include <memory>

namespace Math4BG
{
    class IOutput : private std::streambuf, public std::ostream, public std::enable_shared_from_this<IOutput>
    {
    public:
        IOutput(const IOutput &output);
        ~IOutput() override = default;

        template<typename T>
        std::ostream& operator<<(const T& data_)
        {
            m_outStream << data_;
            return m_outStream;
        }

    protected:
        IOutput(std::ostream &outStream);
        std::ostream &m_outStream;
    };
}

#endif //MATH4BG_IOUTPUT_H
