//
// Created by Benjam on 12-04-21.
//

#include <stdexcept>
#include "Contexts.h"
#include "../IO/OBJLoader.h"
#include "../Utils/FileSplit.h"
#include "../View/Renderer/3D/Texture/BMPTexture.h"
#include "../View/IMGUI/imgui.h"


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
        if(m_contexts.find(id) == m_contexts.end())
            throw std::runtime_error("Context doesn't exist");

        //int contextId = m_contextIds[id];

        Context* context = m_contexts[id];
        delete context;

        m_contexts.erase(id);
        //m_contextIds.erase(id);

        return id;
    }

    Context *Contexts::operator[](int index)
    {
        if (m_contexts.find(index) == m_contexts.end())
            throw std::runtime_error("Context doesn't exist");

        return m_contexts[index];
    }

    ModelData *Contexts::operator[](const std::string &name)
    {
        if(!ModelExists(name))
            return nullptr;

        return &m_models[name];
    }

    int Contexts::CreateContext(const WindowInfo &info, WorldType type, bool windowed)
    {
        Context* context = new Context(info, type);

        m_contexts[m_count] = context;

        return m_count++;
    }

    std::shared_ptr<Contexts> Contexts::Create()
    {
        return std::shared_ptr<Contexts>(static_cast<Contexts *>(new Contexts()));
    }

    bool Contexts::LoadTexture(const std::string &path, const std::string &name)
    {
        FileSplit fileSplit(path);

        if(fileSplit.fileExtension == "bmp")
        {
            std::shared_ptr<BMPTexture> texture = std::make_shared<BMPTexture>(path, GL_TEXTURE_2D);
            m_textures[name] = texture;
            return true;
        }

        return false;
    }

    bool Contexts::LoadModel(const std::string &path, const std::string &name)
    {
        FileSplit fileSplit(path);
        //return std::shared_ptr<OG33RendererSDL>(Renderer3D::Create(window, width, height));
        if(fileSplit.fileExtension == "obj")
        {
            OBJLoader loader;
            ModelData model = loader.LoadModel(path);

            m_models[name] = model;
            return true;
        }

        return false;
    }

    void Contexts::DrawContexts()
    {
        for(const auto& [key, context] : m_contexts)
        {
            context->GetWorld()->UpdateShaders(m_shaders);
            context->Draw();
        }
    }

    std::string Contexts::CreateShader(const std::string &path)
    {
        //--- HARDCODED
        ShaderProgramSource source = ParseShader(path);
        std::shared_ptr<Shader> shader = Shader::CreateShader(source);
        FileSplit fileSplit(path);

        m_shaders[fileSplit.fileWithoutExtension] = shader;

        return fileSplit.fileWithoutExtension;
    }

    std::shared_ptr<Shader> Contexts::GetShaderByName(const std::string &name)
    {
        return m_shaders[name];
    }

    /*bool Contexts::LoadSound(const std::string &path, const std::string &name)
    {
        FileSplit fileSplit(path);

    }*/
}