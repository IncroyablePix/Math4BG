//
// Created by Benjam on 19-05-21.
//

#include "ILanInterpreter.h"

#include <utility>
#include "../../Utils/ColorSwitch.h"

namespace Math4BG
{

    ILanInterpreter::ILanInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output) :
    m_contexts(std::move(contexts)),
    m_output(std::move(output))
    {

    }

    void ILanInterpreter::PrintImplementation(const std::string &message)
    {
        *m_output << message;
    }

    int ILanInterpreter::CreateContextImplementation(const std::string &title, unsigned int width, unsigned int height,
                                                     bool abstract)
    {
        return m_contexts->CreateContext({title, width, height}, abstract);
    }

    void ILanInterpreter::SetCameraPosImplementation(int contextid, float x, float y, float z)
    {
        if(m_contexts->ContextExists(contextid))
            ((*m_contexts)[contextid])->GetWorld()->SetCameraPos({x, y, z});
    }

    void ILanInterpreter::SetCameraRotImplementation(int contextid, float x, float y)
    {
        if(m_contexts->ContextExists(contextid))
            ((*m_contexts)[contextid])->GetWorld()->SetCameraRot({x, y});
    }

    std::string ILanInterpreter::CreateShaderImplementation(const std::string &path)
    {
        std::string name = "";

        name = m_contexts->CreateShader(path);

        return name;
    }

    bool ILanInterpreter::CreateTextureImplementation(const std::string &path, const std::string &name)
    {
        return m_contexts->LoadTexture(path, name);
    }

    bool ILanInterpreter::CreateModelImplementation(const std::string &path, const std::string &name)
    {
        return m_contexts->LoadModel(path, name);
    }

    long long int ILanInterpreter::GetMillisImplementation()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count();
    }

    void ILanInterpreter::SetBackgroundColorImplementation(int contextid, unsigned int color)
    {
        ((*m_contexts)[contextid])->GetWorld()->SetBackgroundColor(color);
    }

    int ILanInterpreter::CreateCubeImplementation(int contextid, const std::string &shaderName, float x, float y, float z)
    {
        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreateCube(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }

        return id;
    }

    int ILanInterpreter::CreatePlaneImplementation(int contextid, const std::string &shaderName, float x, float y, float z)
    {
        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePlane(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }

        return id;
    }

    int ILanInterpreter::CreatePyramidImplementation(int contextid, const std::string &shaderName, float x, float y,
                                                     float z)
    {
        Transform transform = {{x, y, z}};

        int id = -1;

        std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

        if (m_contexts->ContextExists(contextid))
        {
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePyramid(shader, transform);
            m_contexts->SetWorldForObjectId(id, contextid);
        }

        return id;
    }

    int ILanInterpreter::CreateCustomObjectImplementation(int contextid, const std::string &shaderName,
                                                          const std::string &modelName, float x, float y, float z)
    {
        Transform transform({ x, y, z }, { x, y, z }, { 0.0, 0.0, 0.0 }, {1.0f, 1.0f, 1.0f});

        int id = -1;
        if(m_contexts->ModelExists(modelName))
        {
            auto model = ((*m_contexts)[modelName]);

            std::shared_ptr<Shader> shader = m_contexts->GetShaderByName(shaderName);

            if (m_contexts->ContextExists(contextid))
            {
                id = ((*m_contexts)[contextid])->GetWorld()->CreateCustomObject(model, shader, transform);
                m_contexts->SetWorldForObjectId(id, contextid);
            }
        }

        return id;
    }

    bool ILanInterpreter::SetObjectPosImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectPos(id, {x, y, z});

        return out;
    }

    bool ILanInterpreter::SetObjectRotImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectRot(id, {x, y, z});

        return out;
    }

    bool ILanInterpreter::SetObjectScaleImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectScale(id, {x, y, z});

        return out;
    }

    bool ILanInterpreter::SetObjectPosOriginImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if (m_contexts->GetWorldForId(id))
        {
            auto world = m_contexts->GetWorldForId(id)->GetWorld();
            out = world->SetObjectPosOrigin(id, {x, y, z});
        }

        return out;
    }

    bool ILanInterpreter::SetObjectOriginImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if (m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectOrigin(id, {x, y, z});

        return out;
    }

    bool ILanInterpreter::SetObjectTextureImplementation(int id, const std::string &name)
    {
        bool out = false;

        if (m_contexts->TextureExists(name))
        {
            std::shared_ptr<Texture> texture = m_contexts->GetTextureByName(name);

            if (m_contexts->GetWorldForId(id))
                out = m_contexts->GetWorldForId(id)->GetWorld()->SetObjectTexture(id, texture);
        }
        else
        {
            std::stringstream ss;
            ss << "Texture \"" << name << "\" not found!";
            *m_output << ss.str();
        }

        return out;
    }

    bool ILanInterpreter::SetObjectColorImplementation(int id, unsigned int color)
    {
        bool out = false;

        glm::vec4 vectorizedColor(MaskToFloat(color), 1.0f);

        std::shared_ptr<Context> context = m_contexts->GetWorldForId(id);
        if(context)
            out = context->GetWorld()->SetObjectColor(id, vectorizedColor);

        return out;
    }

    bool ILanInterpreter::SetDirectionalLightImplementation(int contextid, float x, float y, float z, float intensity, unsigned int color)
    {
        bool out = false;

        if (m_contexts->ContextExists(contextid))
            out = ((*m_contexts)[contextid])->GetWorld()->SetDirectionalLight(intensity, {x, y, z}, MaskToFloat(color));

        return out;
    }

    int ILanInterpreter::CreatePointLightImplementation(int contextid, float intensity, unsigned int color, float x,
                                                        float y, float z)
    {
        Transform transform({ x, y, z }, { x, y, z }, { 0.0, 0.0, 0.0 }, {1.0f, 1.0f, 1.0f});

        int id = -1;
        if (m_contexts->ContextExists(contextid))
            id = ((*m_contexts)[contextid])->GetWorld()->CreatePointLight(intensity, MaskToFloat(color), transform);

        return id;
    }

    bool ILanInterpreter::SetLightPosImplementation(int id, float x, float y, float z)
    {
        bool out = false;

        if(m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetLightPos(id, {x, y, z});

        return out;
    }

    bool ILanInterpreter::SetLightColorImplementation(int id, unsigned int color)
    {
        bool out = false;
        glm::vec3 col = MaskToFloat(color);

        if(m_contexts->GetWorldForId(id))
            out = m_contexts->GetWorldForId(id)->GetWorld()->SetLightColor(id, MaskToFloat(color));

        return out;
    }
}