//
// Created by Benjam on 12-04-21.
//

#include <stdexcept>
#include "Contexts.h"

Contexts::Contexts()
{

}

Contexts::~Contexts()
{

}

Context* Contexts::operator[](int index)
{
    if(m_contexts.find(index) == m_contexts.end())
        throw std::runtime_error("Context doesn't exist");

    return m_contexts[index];
}

int Contexts::CreateContext(const WindowInfo &info, WorldType type)
{
    m_contexts[m_count] = new Context(info, type);
    return m_count ++;
}

std::shared_ptr<Contexts> Contexts::Create()
{
    return std::shared_ptr<Contexts>(static_cast<Contexts*>(new Contexts()));
}
