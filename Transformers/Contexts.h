//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXTS_H
#define ARCPOSITION_CONTEXTS_H

#include "Context.h"
#include "../IO/IModelLoader.h"

namespace Math4BG
{
    class Contexts : public std::enable_shared_from_this<Contexts>
    {
    public:
        Contexts();
        ~Contexts();

        int CreateContext(const WindowInfo &info, WorldType type);
        inline Context *GetContext(int id) { return m_contexts[id]; }
        inline bool ContextExists(int id) { return m_contexts.find(id) != m_contexts.end(); }
        inline bool ModelExists(const std::string &name) { return m_models.find(name) != m_models.end(); }
        Context *operator[](int index);
        ModelData *operator[](const std::string &name);

        inline Context *GetWorldForId(int id) { return m_contexts[m_objects[id]]; }
        inline std::unordered_map<int, Context *>::iterator Begin() { return m_contexts.begin(); }
        inline std::unordered_map<int, Context *>::iterator End() { return m_contexts.end(); }
        static std::shared_ptr<Contexts> Create();

        int KillContextForWindowId(uint32_t id);

        bool LoadModel(const std::string &path, const std::string &name);
    private:
        std::unordered_map<std::string, ModelData> m_models;
        std::unordered_map<uint32_t, int> m_contextIds;
        std::unordered_map<int, Context*> m_contexts;
        std::unordered_map<int, int> m_objects;
        int m_count = 0;
    };
}

#endif //ARCPOSITION_CONTEXTS_H
