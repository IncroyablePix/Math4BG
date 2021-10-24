//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXTS_H
#define ARCPOSITION_CONTEXTS_H

#include "Context.h"
#include "../IO/IModelLoader.h"
#include "../View/Renderer/3D/Texture/Texture.h"

namespace Math4BG
{
    class Contexts : public std::enable_shared_from_this<Contexts>
    {
    public:
        Contexts();
        ~Contexts();

        int CreateContext(const WindowInfo &info, WorldType type, bool windowed = true);
        inline Context *GetContext(int id) { return m_contexts[id]; }
        inline bool ContextExists(int id) { return m_contexts.find(id) != m_contexts.end() && m_contexts[id] != nullptr; }
        inline bool ModelExists(const std::string &name) { return m_models.find(name) != m_models.end(); }
        inline bool TextureExists(const std::string &name) { return m_textures.find(name) != m_textures.end(); }
        Context *operator[](int index);
        ModelData *operator[](const std::string &name);
        inline std::shared_ptr<Texture> GetTextureByName(const std::string &name) { return m_textures[name]; }
        std::shared_ptr<Shader> GetShaderByName(const std::string &name);

        std::string CreateShader(const std::string &path);

        inline Context *GetWorldForId(int id) { return m_contexts[m_objects[id]]; }
        static std::shared_ptr<Contexts> Create();

        void SetWindowFocused(bool focused);

        int KillContextForWindowId(uint32_t id);

        bool LoadTexture(const std::string &path, const std::string &name);
        bool LoadModel(const std::string &path, const std::string &name);

        //inline Context* ContextFromWindowId(int windowId) { return (m_contextIds.find(windowId) != m_contextIds.end()) ? m_contexts[m_contextIds[windowId]] : nullptr; }

        void Update(double lag);
        void DrawContexts();

    private:
        std::unordered_map<std::string, ModelData> m_models;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
        //std::unordered_map<uint32_t, int> m_contextIds;
        std::unordered_map<int, Context*> m_contexts;
        std::unordered_map<int, int> m_objects;
        int m_count = 0;
    };
}

#endif //ARCPOSITION_CONTEXTS_H
