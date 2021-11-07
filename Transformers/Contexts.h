//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_CONTEXTS_H
#define ARCPOSITION_CONTEXTS_H

#include "Context.h"
#include "../IO/IModelLoader.h"
#include "../View/Renderer/3D/Texture/Texture.h"
#include "../Output/IOutput.h"

namespace Math4BG
{
    class Contexts : public std::enable_shared_from_this<Contexts>
    {
    public:
        explicit Contexts(std::shared_ptr<IOutput> output);
        ~Contexts();

        int CreateContext(const WindowInfo &info, bool abstract);
        inline std::shared_ptr<Context> GetContext(int id) { return m_contexts[id]; }
        inline bool ContextExists(int id) { return m_contexts.find(id) != m_contexts.end() && m_contexts[id] != nullptr; }
        inline bool ModelExists(const std::string &name) { return m_models.find(name) != m_models.end(); }
        inline bool TextureExists(const std::string &name) { return m_textures.find(name) != m_textures.end(); }
        std::shared_ptr<Context> operator[](int index);
        std::shared_ptr<ModelData> operator[](const std::string &name);
        inline std::shared_ptr<Texture> GetTextureByName(const std::string &name) { return m_textures[name]; }
        std::shared_ptr<Shader> GetShaderByName(const std::string &name);

        std::string CreateShader(const std::string &path);

        inline std::shared_ptr<Context> GetWorldForId(int id) { return m_contexts[m_objects[id]]; }
        inline void SetWorldForObjectId(int objectId, int worldId) { m_objects[objectId] = worldId; }
        static std::shared_ptr<Contexts> Create(std::shared_ptr<IOutput> output);

        void SetWindowFocused(bool focused);

        bool LoadTexture(const std::string &path, const std::string &name);
        bool LoadModel(const std::string &path, const std::string &name);

        void Clear();
        void Update(double lag);
        void DrawContexts();

    private:
        std::unordered_map<std::string, std::shared_ptr<ModelData>> m_models;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
        std::unordered_map<int, std::shared_ptr<Context>> m_contexts;
        std::unordered_map<int, int> m_objects;

        std::shared_ptr<Shader> m_basicShader;

        std::shared_ptr<IOutput> m_output;
        int m_count = 0;
    };
}

#endif //ARCPOSITION_CONTEXTS_H
