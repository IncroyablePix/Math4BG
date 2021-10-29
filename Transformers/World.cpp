//
// Created by Benjam on 12-04-21.
//

#include <iostream>
#include "World.h"
#include "../View/Renderer/3D/Object/Cube.h"
#include "../Utils/FileSplit.h"
#include "../View/Renderer/3D/Camera/MainCamera.h"
#include "../View/Renderer/3D/Object/Pyramid.h"
#include "../View/Renderer/3D/Texture/Texture.h"
#include "../View/Renderer/3D/Light/PointLight.h"
#include "../View/Renderer/3D/Object/Plane.h"
#include "../Utils/ColorSwitch.h"
#include "../View/IMGUI/imgui.h"


namespace Math4BG
{
    World::World(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer) :
            m_renderer(std::move(renderer)),
            m_camera(std::make_unique<MainCamera>(45.0f, (float) info.width, (float) info.height, 0.1f, 1000.0f)),
            m_directionalLight({0.7f, -0.7f, 0.0f}, 1.0f, {1.0f, 1.0f, 1.0f}),
            m_fbo(info.width, info.height)
    {
    }

    World::~World()
    {

    }

    void World::DrawWorld()
    {
        m_fbo.Bind(true); // Draw everything to frame buffer
        m_renderer->Clear();

        for(const auto& [index, drawable] : m_objects)
            m_renderer->Draw(m_camera.get(), drawable.get());

        m_fbo.Unbind();
    }

    void World::Draw(const std::string &title)
    {
        //window.DrawGUI();

        m_tabActive = false;
        if(ImGui::BeginTabItem(title.c_str()))
        {
            m_tabActive = true;

            ImGui::BeginChild("GameRender");

            // Get the size of the child (i.e. the whole draw size of the windows).
            ImVec2 windowSize = ImGui::GetWindowSize();
            auto pos = ImGui::GetCursorScreenPos();
            //m_fbo.SetSize(windowSize.x, windowSize.y);
            m_camera->SetViewportSize(windowSize.x, windowSize.y);
            DrawWorld();
            // Because I use the texture from OpenGL, I need to invert the V from the UV.

            //auto fboId = (ImTextureID) m_fbo.GetId();
            auto fboId = (void *) (m_fbo.GetTexture()->GetId());
            //ImGui::Image(fboId, windowSize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::GetWindowDrawList()->AddImage(fboId, ImVec2(pos), ImVec2(pos.x + windowSize.x, pos.y + windowSize.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        m_canvas.Bind(*m_ppShader, *m_fbo.GetTexture()); // Drawing frame buffer over canvas
    }

    void World::SetCameraPos(const glm::vec3& pos)
    {
        m_camera->SetCameraPos(pos);
    }

    void World::SetCameraRot(const glm::vec2& pos)
    {
        m_camera->SetCameraRot(pos);
    }

    void World::Update(double lag)//, const MouseInput &mouse, const KeyInput &keys)
    {
        HandleMouseInputs();
        HandleKeyboardInputs();

        m_camera->Update(m_mouse, m_keys, lag);

        m_fbo.Bind(true);
        m_renderer->Clear();
        m_fbo.Unbind();
    }

    void World::SetBackgroundColor(unsigned int color)
    {
        uint8_t r = color >> 24;
        uint8_t g = color >> 16;
        uint8_t b = color >> 8;

        m_renderer->SetBackgroundColor(r, g, b);
    }

    int World::CreateCube(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[m_count] = std::make_shared<Cube>(std::move(shader), transform);
        return m_count++;
    }

    int World::CreatePlane(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[m_count] = std::make_shared<Plane>(std::move(shader), transform);
        return m_count++;
    }

    int World::CreatePyramid(std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[m_count] = std::make_shared<Pyramid>(std::move(shader), transform);
        return m_count++;
    }

    bool World::SetObjectColor(int objid, const glm::vec4 &color)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(IDrawable* o = dynamic_cast<IDrawable*>(object))
            {
                o->SetColor(color);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectPos(int objid, const glm::vec3 &position)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetPos(position);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectOrigin(int objid, const glm::vec3 &position)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetOrigin(position);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectPosOrigin(int objid, const glm::vec3 &position)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetPos(position);
                o->SetOrigin(position);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectRot(int objid, const glm::vec3 &rot)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetRotation(rot);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectScale(int objid, const glm::vec3 &scale)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetScale(scale);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectTexture(int objid, std::shared_ptr<Texture> texture)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
            {
                o->SetTexture(texture);
                return true;
            }
        }
        return false;
    }

    bool World::SetObjectColor(int objid, const glm::vec3 &color)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(IDrawable* o = dynamic_cast<IDrawable*>(object))
            {
                o->SetColor({color, 1.0f});
                return true;
            }
        }
        return false;
    }

    int World::CreateCustomObject(std::shared_ptr<ModelData> model, std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[m_count] = std::make_shared<Object3D>(std::move(shader), std::move(model), transform);
        return m_count++;
    }

    int World::CreatePointLight(float intensity, const glm::vec3 &color, const Transform &transform)
    {
        m_lights[m_count] = std::make_shared<PointLight>(transform, intensity, color);
        return m_count ++;
    }

    bool World::SetDirectionalLight(float intensity, const glm::vec3 &orientation, const glm::vec3 &color)
    {
        m_directionalLight = {orientation, intensity, color};
        return true;
    }

    bool World::SetLightPos(int lightid, const glm::vec3 &position)
    {
        if(m_lights.find(lightid) != m_lights.end())
        {
            auto light = m_lights[lightid].get();
            if(Light* l = dynamic_cast<Light*>(light))
            {
                l->SetPos(position);
                return true;
            }
        }
        return false;
    }

    bool World::SetLightColor(int lightid, const glm::vec3 &color)
    {
        if(m_lights.find(lightid) != m_lights.end())
        {
            auto light = m_lights[lightid].get();
            if(Light* l = dynamic_cast<Light*>(light))
            {
                l->SetColor(color);
                return true;
            }
        }
        return false;
    }

    void World::Resize(int width, int height)
    {
        m_camera->SetViewportSize(width, height);
        m_renderer->Resize(width, height);
    }

    void World::UpdateShader(std::shared_ptr<Shader> shader)
    {
        Shader* shaderProgram = shader.get();

        shaderProgram->Bind();
        shaderProgram->SetUniformVec2("vPixelSize", m_camera->GetPixelSize());
        m_directionalLight.ToShader(*shaderProgram);

        for(const auto& [id, light] : m_lights)
        {
            light->ToShader(*shaderProgram);
        }

        shaderProgram->Unbind();
    }

    void World::HandleMouseInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        if(m_tabActive)//if(m_windowActive)// && m_tabActive)
        {
            m_mouse.MouseSet(LMB, ImGui::IsMouseDown(ImGuiMouseButton_Left));
            m_mouse.MouseSet(RMB, ImGui::IsMouseDown(ImGuiMouseButton_Right));
            m_mouse.MouseSet(MMB, ImGui::IsMouseDown(ImGuiMouseButton_Middle));
            //m_mouse.MouseSet(MWU, ImGui::IsMouseClicked(ImGuiMouseWheel));
            //m_mouse.MouseSet(MWD, ImGui::IsMouseClicked(4));

            m_mouse.MousePos({ImGui::GetMousePos().x, ImGui::GetMousePos().y});
        }
    }

    void World::HandleKeyboardInputs()
    {
        ImGuiIO& io = ImGui::GetIO();
        if(m_tabActive)//if(m_windowActive)// && m_tabActive)
        {
            m_keys.KeySet(Z, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow)));
            m_keys.KeySet(S, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow)));
            m_keys.KeySet(Q, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow)));
            m_keys.KeySet(D, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow)));
            m_keys.KeySet(PgUp, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageUp)));
            m_keys.KeySet(PgDn, ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_PageDown)));
            //m_keys.KeySet(S, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_S)));
            //m_keys.KeySet(Q, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_A)));
            //m_keys.KeySet(D, ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_)));
        }
    }
}