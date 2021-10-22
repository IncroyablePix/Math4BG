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
    World::World(const WindowInfo &info, WorldType type, std::shared_ptr<OG33Renderer> renderer) :
            m_renderer(std::move(renderer)),
            m_type(type),
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
    void World::Draw(const std::string &title)
    {
        //window.DrawGUI();

        if(ImGui::BeginTabItem(title.c_str()))
        {
            ImGui::BeginChild("GameRender");
            // Get the size of the child (i.e. the whole draw size of the windows).
            ImVec2 wsize = ImGui::GetWindowSize();
            m_camera->SetViewportSize(wsize.x, wsize.y);
            DrawWorld();
            // Because I use the texture from OpenGL, I need to invert the V from the UV.
            ImGui::Image((ImTextureID) m_fbo.GetId(), wsize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        m_canvas.Bind(*m_ppShader, *m_fbo.GetTexture()); // Drawing frame buffer over canvas
    }
#pragma clang diagnostic pop

    void World::SetCameraPos(const glm::vec3& pos)
    {
        m_camera->SetCameraPos(pos);
    }

    void World::SetCameraRot(const glm::vec2& pos)
    {
        m_camera->SetCameraRot(pos);
    }

    /*std::string World::CreateShader(const std::string &path)
    {
        //--- HARDCODED
        ShaderProgramSource source = ParseShader(path);
        std::shared_ptr<Shader> shader = Shader::CreateShader(source);
        FileSplit fileSplit(path);

        m_shaders[fileSplit.fileWithoutExtension] = shader;

        return fileSplit.fileWithoutExtension;
    }*/

    void World::Update(double lag, const MouseInput &mouse, const KeyInput &keys)
    {
        m_camera->Update(mouse, keys, lag);

        m_fbo.Bind(true);
        m_renderer->Clear();
        m_fbo.Unbind();
    }

    int World::CreateCircle(std::shared_ptr<Shader> shader, const glm::vec3 &center, double radius, uint32_t color)
    {
        m_objects[m_count] = std::make_shared<Circle>(std::move(shader), center, radius, color);
        //m_circles[m_count] = {center, radius, color};
        return m_count++;
    }

    bool World::SetCirclePos(int circleid, Point center)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->m_center.x = center.x;
                c->m_center.y = center.y;
                return true;
            }
        }

        return false;
    }

    bool World::SetCircleSize(int circleid, double radius)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->m_radius = radius;
                return true;
            }
        }

        return false;
    }

    int World::CreateLine(std::shared_ptr<Shader> shader, const glm::vec3 &start, const glm::vec3 &end, uint32_t color)
    {
        m_objects[m_count] = std::make_shared<Line>(std::move(shader), start, end, color);
        //m_lines[m_count] = { start, end, color };
        return m_count++;
    }

    bool World::SetLinePos(int lineid, Point start, Point end)
    {
        if (m_objects.find(lineid) != m_objects.end())
        {
            auto line = m_objects[lineid].get();
            if(Line* r = dynamic_cast<Line*>(line))
            {
                r->m_start = {start.x, start.y, 1.0f};
                r->m_end = {end.x, end.y, 1.0f};
                return true;
            }
        }
        return false;
        /*if (m_objects.find(lineid) != m_objects.end())
        {
            m_lines[lineid].m_start = {start.x, start.y, 1.0f};
            m_lines[lineid].m_end = {end.x, end.y, 1.0f};
            return true;
        }

        return false;*/
    }

    void World::SetBackgroundColor(unsigned int color)
    {
        uint8_t r = color >> 24;
        uint8_t g = color >> 16;
        uint8_t b = color >> 8;

        m_renderer->SetBackgroundColor(r, g, b);
    }

    int World::CreateRectangle(std::shared_ptr<Shader> shader, const glm::vec3 &position, float width, float height, uint32_t color)
    {
        //m_objects[m_count] = std::make_shared<Line>(start, end, color);
        glm::vec2 dimens = {width, height};
        m_objects[m_count] = std::make_shared<Rectangle>(std::move(shader), position, dimens, color);
        return m_count++;
    }

    bool World::SetRectanglePos(int rectangleid, Point position)
    {
        if (m_objects.find(rectangleid) != m_objects.end())
        {
            auto rectangle = m_objects[rectangleid].get();
            if(Rectangle* r = dynamic_cast<Rectangle*>(rectangle))
            {
                r->m_start = position;
                return true;
            }
        }
        return false;
    }

    bool World::SetRectangleDimens(int rectangleid, int width, int height)
    {
        if (m_objects.find(rectangleid) != m_objects.end())
        {
            auto rectangle = m_objects[rectangleid].get();
            if(Rectangle* r = dynamic_cast<Rectangle*>(rectangle))
            {
                r->m_width = width;
                r->m_height = height;
                return true;
            }
        }
        return false;
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

    int World::CreateCustomObject(ModelData *model, std::shared_ptr<Shader> shader, Transform &transform)
    {
        m_objects[m_count] = std::make_shared<Object3D>(std::move(shader), model, transform);
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

    void World::UpdateShaders(std::unordered_map<std::string, std::shared_ptr<Shader>> &shaders)
    {
        for(const auto& [name, shader] : shaders)
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
    }
}