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


namespace Math4BG
{
    World::World(const WindowInfo &info, WorldType type, std::shared_ptr<IRenderer> renderer) :
            m_renderer(std::move(renderer)),
            m_type(type),
            m_camera(std::make_unique<MainCamera>(45.0f, (float) info.width / (float) info.height, 0.1f, 1000.0f)),
            m_directionalLight({-0.7f, -0.7f, 0.0f}, 1.0f, {1.0f, 1.0f, 1.0f})
    {
    }

    World::~World()
    {

    }

    void World::SetCameraPos(const glm::vec3& pos)
    {
        m_camera->SetCameraPos(pos);
    }

    std::string World::CreateShader(const std::string &path)
    {
        //--- HARDCODED
        ShaderProgramSource source = ParseShader(path);
        std::shared_ptr<Shader> shader = Shader::CreateShader(source);
        FileSplit fileSplit(path);
        std::cout << fileSplit.fileWithoutExtension << std::endl;
        /*shader->Bind();
        shader->SetUniformVec4("vColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
        shader->Unbind();*/

        m_shaders[fileSplit.fileWithoutExtension] = shader;

        return fileSplit.fileWithoutExtension;
    }

    void World::Update(double lag)
    {
        m_camera->Update(lag);
    }

    int World::CreateCircle(Point center, double radius, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<Circle>(center, radius, color);
            //m_circles[m_count] = {center, radius, color};
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
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

    bool World::SetCircleColor(int circleid, uint32_t color)
    {
        if (m_objects.find(circleid) != m_objects.end())
        {
            auto circle = m_objects[circleid].get();
            if(Circle* c = dynamic_cast<Circle*>(circle))
            {
                c->SetColor(color);
                return true;
            }
        }

        return false;
    }

    int World::CreateLine(Point start, Point end, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<Line>(start, end, color);
            //m_lines[m_count] = { start, end, color };
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    bool World::SetLinePos(int lineid, Point start, Point end)
    {
        if (m_lines.find(lineid) != m_lines.end())
        {
            m_lines[lineid].m_start = start;
            m_lines[lineid].m_end = end;
            return true;
        }

        return false;
    }

    bool World::SetLineColor(int lineid, uint32_t color)
    {
        if (m_lines.find(lineid) != m_lines.end())
        {
            m_lines[lineid].SetColor(color);
            return true;
        }

        return false;
    }

    void World::SetBackgroundColor(unsigned int color)
    {
        uint8_t r = color >> 24;
        uint8_t g = color >> 16;
        uint8_t b = color >> 8;

        m_renderer->SetBackgroundColor(r, g, b);
    }

    void World::Draw(Window &window)
    {
        if(m_type == WorldType::Relief)
        {
            for (std::pair<std::string, std::shared_ptr<Shader>> shader : m_shaders)
            {
                shader.second->Bind();
                m_directionalLight.ToShader(*shader.second);

                for (std::pair<int, std::shared_ptr<Light>> light : m_lights)
                {
                    light.second->ToShader(*shader.second);
                }
                shader.second->Unbind();
            }
        }
        //m_camera->Move(m_camera->Backward() + (m_camera->Left() * 0.5f), 0.05f); // Hardcoded
        //m_camera->Rotate({0.0, 0.01, 0.0});
        for(const auto& drawable : m_objects)
            window.Draw(m_camera.get(), drawable.second.get());
    }

    int World::CreateDot(Point position, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            m_objects[m_count] = std::make_shared<SinglePixel>(position, color);
            //m_circles[m_count] = {center, radius, color};
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
        return 0;
    }

    bool World::SetDotPos(int dotid, Point position)
    {
        if (m_objects.find(dotid) != m_objects.end())
        {
            auto point = m_objects[dotid].get();
            if(SinglePixel* p = dynamic_cast<SinglePixel*>(point))
            {
                p->SetPosition(position);
                return true;
            }
        }

        return false;
    }

    bool World::SetDotColor(int dotid, uint32_t color)
    {
        if (m_objects.find(dotid) != m_objects.end())
        {
            auto circle = m_objects[dotid].get();
            if(SinglePixel* p = dynamic_cast<SinglePixel*>(circle))
            {
                p->SetColor(color);
                return true;
            }
        }

        return false;
    }

    int World::CreateRectangle(Point position, int width, int height, uint32_t color)
    {
        if(m_type == WorldType::Flat)
        {
            //m_objects[m_count] = std::make_shared<Line>(start, end, color);
            m_objects[m_count] = std::make_shared<Rectangle>(position, width, height, color);
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
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

    bool World::SetRectangleColor(int rectangleid, uint32_t color)
    {
        if (m_objects.find(rectangleid) != m_objects.end())
        {
            auto rectangle = m_objects[rectangleid].get();
            if(Rectangle* r = dynamic_cast<Rectangle*>(rectangle))
            {
                r->SetColor(color);
                return true;
            }
        }
        return false;
    }

    int World::CreateCube(const std::string &shaderName, Transform &transform)
    {
        if(m_type == WorldType::Relief)
        {
            m_objects[m_count] = std::make_shared<Cube>(m_shaders[shaderName], transform);
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    int World::CreatePlane(const std::string &shaderName, Transform &transform)
    {
        if(m_type == WorldType::Relief)
        {
            m_objects[m_count] = std::make_shared<Plane>(m_shaders[shaderName], transform);
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    int World::CreatePyramid(const std::string &shaderName, Transform &transform)
    {
        if(m_type == WorldType::Relief)
        {
            m_objects[m_count] = std::make_shared<Pyramid>(m_shaders[shaderName], transform);
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    bool World::SetObjectColor(int objid, const glm::vec4 &color)
    {
        if(m_objects.find(objid) != m_objects.end())
        {
            auto object = m_objects[objid].get();
            if(Object3D* o = dynamic_cast<Object3D*>(object))
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

    int World::CreateCustomObject(ModelData *model, const std::string &shaderName, Transform &transform)
    {
        if(m_type == WorldType::Relief)
        {
            m_objects[m_count] = std::make_shared<Object3D>(m_shaders[shaderName], model, transform);
            return m_count++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    int World::CreatePointLight(float intensity, const glm::vec3 &color, const Transform &transform)
    {
        if(m_type == WorldType::Relief)
        {
            m_lights[m_count] = std::make_shared<PointLight>(transform, intensity, color);
            return m_count ++;
        }
        else
        {
            return INVALID_OBJECT_ID;
        }
    }

    bool World::SetDirectionalLight(float intensity, const glm::vec3 &orientation, const glm::vec3 &color)
    {
        if(m_type == WorldType::Relief)
        {
            //DirectionalLight light(orientation, intensity, color);
            m_directionalLight = {orientation, intensity, color};
            return true;
        }
        else
        {
            return false;
        }
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
}