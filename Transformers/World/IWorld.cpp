//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include <utility>
#include "IWorld.h"
#include "../../View/Renderer/3D/Object/Cube.h"
#include "../../Utils/FileSplit.h"
#include "../../View/Renderer/3D/Camera/MainCamera.h"
#include "../../View/Renderer/3D/Object/Pyramid.h"
#include "../../View/Renderer/3D/Texture/Texture.h"
#include "../../View/Renderer/3D/Light/PointLight.h"
#include "../../View/Renderer/3D/Object/Plane.h"
#include "../../Utils/ColorSwitch.h"
#include "../../View/IMGUI/imgui.h"


namespace Math4BG
{
    IWorld::IWorld(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer) :
            m_renderer(std::move(renderer)),
            m_camera(std::make_unique<MainCamera>(45.0f, (float) info.width, (float) info.height, 0.1f, 1000.0f)),
            m_directionalLight({0.7f, -0.7f, 0.0f}, 1.0f, {1.0f, 1.0f, 1.0f}),
            m_fbo(info.width, info.height)
    {
    }

    IWorld::~IWorld()
    {

    }

    void IWorld::DrawWorld()
    {
        m_fbo.Bind(true); // Draw everything to frame buffer
        m_renderer->Clear();

        for (const auto&[index, drawable]: m_objects)
            m_renderer->Draw(m_camera.get(), drawable.get());

        m_fbo.Unbind();
    }

    void IWorld::SetCameraPos(const glm::vec3 &pos)
    {
        m_camera->SetCameraPos(pos);
    }

    void IWorld::SetCameraRot(const glm::vec2 &pos)
    {
        m_camera->SetCameraRot(pos);
    }

    void IWorld::Update(double lag)//, const MouseInput &mouse, const KeyInput &keys)
    {
        m_fbo.Bind(true);
        m_renderer->Clear();
        m_fbo.Unbind();
    }

    void IWorld::SetBackgroundColor(unsigned int color)
    {
        uint8_t r = color >> 24;
        uint8_t g = color >> 16;
        uint8_t b = color >> 8;

        m_renderer->SetBackgroundColor(r, g, b);
    }

    int IWorld::CreateCube(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[objectsCount] = std::make_shared<Cube>(std::move(shader), transform);
        return objectsCount++;
    }

    int IWorld::CreatePlane(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[objectsCount] = std::make_shared<Plane>(std::move(shader), transform);
        return objectsCount++;
    }

    int IWorld::CreatePyramid(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[objectsCount] = std::make_shared<Pyramid>(std::move(shader), transform);
        return objectsCount++;
    }

    bool IWorld::SetObjectColor(int objid, const glm::vec4 &color)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<IDrawable *>(object))
            {
                o->SetColor(color);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectPos(int objid, const glm::vec3 &position)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetPos(position);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectOrigin(int objid, const glm::vec3 &position)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetOrigin(position);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectPosOrigin(int objid, const glm::vec3 &position)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetPos(position);
                o->SetOrigin(position);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectRot(int objid, const glm::vec3 &rot)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetRotation(rot);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectScale(int objid, const glm::vec3 &scale)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetScale(scale);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectTexture(int objid, std::shared_ptr<Texture> texture)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<Object3D *>(object))
            {
                o->SetTexture(std::move(texture));
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetObjectColor(int objid, const glm::vec3 &color)
    {
        if (m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if (auto *o = dynamic_cast<IDrawable *>(object))
            {
                o->SetColor({color, 1.0f});
                return true;
            }
        }
        return false;
    }

    int IWorld::CreateCustomObject(std::shared_ptr<ModelData> model, std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[objectsCount] = std::make_shared<Object3D>(std::move(shader), std::move(model), transform);
        return objectsCount++;
    }

    int IWorld::CreatePointLight(float intensity, const glm::vec3 &color, const Transform &transform)
    {
        m_lights[objectsCount] = std::make_shared<PointLight>(transform, intensity, color);
        return objectsCount++;
    }

    bool IWorld::SetDirectionalLight(float intensity, const glm::vec3 &orientation, const glm::vec3 &color)
    {
        m_directionalLight = {orientation, intensity, color};
        return true;
    }

    bool IWorld::SetLightPos(int lightid, const glm::vec3 &position)
    {
        if (m_lights.find(lightid) != m_lights.end())
        {
            auto light = m_lights[lightid].get();
            if (auto *l = dynamic_cast<Light *>(light))
            {
                l->SetPos(position);
                return true;
            }
        }
        return false;
    }

    bool IWorld::SetLightColor(int lightid, const glm::vec3 &color)
    {
        if (m_lights.find(lightid) != m_lights.end())
        {
            auto light = m_lights[lightid].get();
            if (auto *l = dynamic_cast<Light *>(light))
            {
                l->SetColor(color);
                return true;
            }
        }
        return false;
    }

    void IWorld::Resize(int width, int height)
    {
        m_camera->SetViewportSize(width, height);
        m_renderer->Resize(width, height);
    }

    void IWorld::UpdateShader(std::shared_ptr<Shader> shader)
    {
        Shader *shaderProgram = shader.get();

        shaderProgram->Bind();
        shaderProgram->SetUniformVec2("vPixelSize", m_camera->GetPixelSize());
        m_directionalLight.ToShader(*shaderProgram);

        for (const auto&[id, light]: m_lights)
        {
            light->ToShader(*shaderProgram);
        }

        shaderProgram->Unbind();
    }
}