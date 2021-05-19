//
// Created by Benjam on 12-04-21.
//

#include <stdexcept>
#include "Contexts.h"


namespace Math4BG
{
    Contexts::Contexts()
    {

    }

    Contexts::~Contexts()
    {

    }

    int Contexts::KillContextForWindowId(uint32_t id)
    {
        if(m_contextIds.find(id) == m_contextIds.end())
            throw std::runtime_error("Context doesn't exist");

        int contextId = m_contextIds[id];

        Context* context = m_contexts[contextId];
        delete context;

        m_contexts.erase(contextId);
        m_contextIds.erase(id);

        return contextId;
    }

    Context *Contexts::operator[](int index)
    {
        if (m_contexts.find(index) == m_contexts.end())
            throw std::runtime_error("Context doesn't exist");

        return m_contexts[index];
    }

    int Contexts::CreateContext(const WindowInfo &info, WorldType type)
    {
        Context* context = new Context(info, type);

        m_contexts[m_count] = context;
        m_contextIds[context->GetWindowId()] = m_count;

        return m_count++;
    }

    std::shared_ptr<Contexts> Contexts::Create()
    {
        return std::shared_ptr<Contexts>(static_cast<Contexts *>(new Contexts()));
    }
}