//
// Created by Benjam on 12-04-21.
//

#include <stdexcept>
#include "Contexts.h"
#include "../IO/OBJLoader.h"
#include "../Utils/FileSplit.h"
#include "../View/Renderer/3D/Texture/BMPTexture.h"
#include "../View/IMGUI/imgui.h"
#include "../IO/IOException.h"
#include "../View/Renderer/3D/Shaders/ShaderException.h"


namespace Math4BG
{
    Contexts::Contexts(std::shared_ptr<IOutput> output) : m_output(std::move(output))
    {

    }

    Contexts::~Contexts()
    {
        Clear();
    }

    std::shared_ptr<Context> Contexts::operator[](int index)
    {
        if (m_contexts.find(index) == m_contexts.end())
            throw std::runtime_error("Context doesn't exist");

        return m_contexts[index];
    }

    std::shared_ptr<ModelData> Contexts::operator[](const std::string &name)
    {
        if(!ModelExists(name))
            return nullptr;

        return m_models[name];
    }

    int Contexts::CreateContext(const WindowInfo &info)
    {
        m_contexts[m_count] = std::make_shared<Context>(info);

        return m_count++;
    }

    std::shared_ptr<Contexts> Contexts::Create(std::shared_ptr<IOutput> output)
    {
        return std::shared_ptr<Contexts>(static_cast<Contexts *>(new Contexts(std::move(output))));
    }

    bool Contexts::LoadTexture(const std::string &path, const std::string &name)
    {
        FileSplit fileSplit(path);

        if(fileSplit.fileExtension == "bmp")
        {
            try
            {
                std::shared_ptr<BMPTexture> texture = std::make_shared<BMPTexture>(path, GL_TEXTURE_2D);
                m_textures[name] = texture;
                return true;
            }
            catch(const IOException& e)
            {
                *m_output << e.what();
            }
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
            m_models[name] = std::move(loader.LoadModel(path));
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
        try
        {
            ShaderProgramSource source = ParseShader(path);
            std::shared_ptr<Shader> shader = Shader::CreateShader(source);
            FileSplit fileSplit(path);

            m_shaders[fileSplit.fileWithoutExtension] = shader;

            return fileSplit.fileWithoutExtension;
        }
        catch(const ShaderException &e)
        {
            *m_output << e.what();
            return "";
        }
    }

    std::shared_ptr<Shader> Contexts::GetShaderByName(const std::string &name)
    {
        return m_shaders[name];
    }

    void Contexts::Update(double lag)
    {
        for(const auto& [id, context] : m_contexts)
            context->Update(lag);
    }

    void Contexts::SetWindowFocused(bool focused)
    {
        for(const auto& [id, context] : m_contexts)
            context->GetWorld()->SetWindowActive(focused);
    }

    void Contexts::Clear()
    {
        m_shaders.clear();
        m_textures.clear();
        m_models.clear();
        m_objects.clear();
        m_contexts.clear();

        m_count = 0;
    }

    /*bool Contexts::LoadSound(const std::string &path, const std::string &name)
    {
        FileSplit fileSplit(path);

    }*/
}